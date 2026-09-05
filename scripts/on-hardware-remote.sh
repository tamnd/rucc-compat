#!/bin/sh
# The half of `on-hardware.sh` that runs on the machine being measured.
#
# It is a file rather than a string the other half builds, so that the quoting is a shell script
# somebody can read, and so that a machine that goes red can be worked on by hand: ssh in, cd to
# the directory, and run this again. It reads three things out of the environment because ssh
# does not forward one, and works the rest out from the machine it is on, which is the point.
#
#   ON_HARDWARE_ROOT     the directory holding compat/ and rucc/, relative to the home directory
#   ON_HARDWARE_LEVELS   the optimization levels to run
#   ON_HARDWARE_CC       the reference compiler, or empty to work one out
#
# It keeps going after a failure and reports at the end. A run that stops on the first red corpus
# measures one corpus.

set -u

root=${ON_HARDWARE_ROOT:-rucc-hardware}
levels=${ON_HARDWARE_LEVELS:-"0 1 2 3 s z"}
cc=${ON_HARDWARE_CC:-}

# The corpora, named rather than discovered, so that a corpus added tomorrow is a line in this
# file somebody thought about rather than an hour added to every run without anybody noticing.
# tcc and sqlite name no oracle, so they are checked and not executed.
pipeline_corpora="c-testsuite chibicc gcc-torture tcc sqlite"
exec_corpora="c-testsuite chibicc gcc-torture"
differential_corpora="glibc musl"

# cargo is not on the PATH of a non interactive ssh session on most machines, because rustup puts
# it there from a profile that a non interactive shell does not read. Sourcing the file it wrote
# is the usual fix, and adding the directory covers the machine where the toolchain is there but
# the file is not, which is what an old rustup or a hand moved home directory leaves behind.
if [ -f "$HOME/.cargo/env" ]; then
  . "$HOME/.cargo/env"
fi
if [ -d "$HOME/.cargo/bin" ]; then
  PATH=$HOME/.cargo/bin:$PATH
  export PATH
fi
if ! command -v cargo >/dev/null 2>&1; then
  echo "on-hardware: no cargo on this machine" >&2
  exit 2
fi

cd "$HOME/$root" || exit 2
uname -sm

cargo build --release --manifest-path rucc/Cargo.toml --bin rucc || exit 2
cargo build --release --manifest-path compat/Cargo.toml || exit 2

ruccbin=$PWD/rucc/target/release/rucc
cd compat || exit 2
compat=./target/release/rucc-compat

# The reference is worked out here rather than written down, because the whole point of running
# on somebody else's machine is that theirs is not ours. A machine with no gcc 16 is still worth
# running: it measures the same compiler against a different reference, and the report names what
# it used, so the number is readable rather than mysterious.
if [ -z "$cc" ]; then
  for candidate in gcc-16 /opt/gcc-16.2.0/bin/gcc-16 gcc cc; do
    if command -v "$candidate" >/dev/null 2>&1; then
      cc=$candidate
      break
    fi
  done
fi
if [ -z "$cc" ]; then
  echo "on-hardware: no reference compiler on this machine" >&2
  exit 2
fi
ccversion=$("$cc" --version | head -1)
echo "$ccversion"

# The exclusion lists are written against gcc 16, and staleness is measured against whatever
# reference is here. An older gcc accepts programs gcc 16 refuses, so cases that are skipped on a
# gcc 16 machine run on this one and some of them pass, which reads as a stale entry and is not
# one. So staleness is only red where the reference is the one the lists were written against.
# Anywhere else it is printed and the run is still judged on failures, which mean the same thing
# whatever the reference is.
case $ccversion in
  *' 16.'*) stale_is_red=1 ;;
  *) stale_is_red=0 ;;
esac
if [ "$stale_is_red" -eq 0 ]; then
  echo "on-hardware: the reference is not gcc 16, so stale entries are reported and not red"
fi

# How many levels run at once and how many of the harness's own jobs each of them gets, so that
# six levels at once do not ask for six times the machine. The scratch directory carries the
# level, which is what makes running them at once safe at all.
#
# A small machine runs them in batches rather than all at once. Six sweeps on four cores is six
# processes competing for one core each and a compiler in memory for every one of them, and the
# machines this is pointed at are somebody's machines, so a run that leaves one of them swapping
# is worse than a run that takes twice as long.
cores=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)
count=$(printf '%s\n' $levels | wc -l | tr -d ' ')
batch=$count
if [ "$batch" -gt "$cores" ]; then
  batch=$cores
fi
if [ "$batch" -lt 1 ]; then
  batch=1
fi
jobs=$((cores / batch))
if [ "$jobs" -lt 1 ]; then
  jobs=1
fi
echo "on-hardware: $cores cores, $batch levels at a time, $jobs jobs each"
machine=$(uname -sm | tr ' ' '-')

bad=0

# The logs go where the reports go, because that directory is the one the other half copies back
# and a log that stayed on the machine is a log nobody reads.
mkdir -p results

echo
echo "-- fetching"
# A corpus that will not come down is not a compiler result and is not this machine's fault. It is
# a tarball on somebody's server, and savannah answering 504 for an afternoon has nothing to say
# about the compiler. So the ones that fail are named here, dropped from the rest of the run, and
# said again at the end, and they do not turn the machine red. What is not allowed is the quiet
# version, where the fetch fails, the check says the corpus is not there, and the run goes red
# for a reason nobody can read.
missing=""
for corpus in $pipeline_corpora; do
  if ! $compat fetch "$corpus" >"results/fetch-$corpus.log" 2>&1; then
    echo "could not fetch $corpus, so it is not measured here. The last of it:"
    tail -3 "results/fetch-$corpus.log"
    missing="$missing $corpus"
  fi
done

# The corpora that are actually here, in the order they were named.
kept() {
  for one in $1; do
    skip=0
    for gone in $missing; do
      if [ "$one" = "$gone" ]; then
        skip=1
      fi
    done
    if [ "$skip" -eq 0 ]; then
      printf '%s ' "$one"
    fi
  done
  return 0
}
pipeline_corpora=$(kept "$pipeline_corpora")
exec_corpora=$(kept "$exec_corpora")

echo
echo "-- differential"
for corpus in $differential_corpora; do
  for unit in standard posix; do
    CC=$cc $compat run "$corpus" --unit "$unit" --rucc "$ruccbin" --report || bad=1
  done
done

echo
echo "-- pipeline"
for corpus in $pipeline_corpora; do
  $compat check "$corpus" --rucc "$ruccbin" --report || bad=1
done

echo
echo "-- execution"
for corpus in $exec_corpora; do
  running=0
  for level in $levels; do
    $compat exec "$corpus" --rucc "$ruccbin" --cc "$cc" --opt "$level" --jobs "$jobs" \
      --machine "$machine" --report > "results/exec-$corpus-$level.log" 2>&1 &
    running=$((running + 1))
    if [ "$running" -ge "$batch" ]; then
      wait
      running=0
    fi
  done
  wait
  for level in $levels; do
    log="results/exec-$corpus-$level.log"
    printf '%s -O%s: ' "$corpus" "$level"
    grep 'runs,' "$log" || echo "no summary, the whole of it is in $log"
    if ! grep -q ', 0 stale' "$log"; then
      [ "$stale_is_red" -eq 1 ] && bad=1
    fi
    grep -qE ', 0 wrong answer, 0 crashed, 0 timed out, 0 did not build' "$log" || bad=1
  done
done

if [ -n "$missing" ]; then
  echo
  echo "on-hardware: not measured here because they would not download:$missing"
fi

exit $bad
