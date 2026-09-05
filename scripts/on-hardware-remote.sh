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
# is the whole fix and it is harmless where there is no such file.
if [ -f "$HOME/.cargo/env" ]; then
  . "$HOME/.cargo/env"
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
"$cc" --version | head -1

# How many of the harness's own jobs each level gets, so that six levels at once do not ask for
# six times the machine. The scratch directory carries the level, which is what makes running
# them at once safe at all.
cores=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)
count=$(printf '%s\n' $levels | wc -l | tr -d ' ')
jobs=$((cores / count))
if [ "$jobs" -lt 1 ]; then
  jobs=1
fi
machine=$(uname -sm | tr ' ' '-')

bad=0

# The logs go where the reports go, because that directory is the one the other half copies back
# and a log that stayed on the machine is a log nobody reads.
mkdir -p results

echo
echo "-- fetching"
for corpus in $pipeline_corpora; do
  $compat fetch "$corpus" >/dev/null 2>&1 || true
done

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
  for level in $levels; do
    $compat exec "$corpus" --rucc "$ruccbin" --cc "$cc" --opt "$level" --jobs "$jobs" \
      --machine "$machine" --report > "results/exec-$corpus-$level.log" 2>&1 &
  done
  wait
  for level in $levels; do
    log="results/exec-$corpus-$level.log"
    printf '%s -O%s: ' "$corpus" "$level"
    grep 'runs,' "$log" || echo "no summary, the whole of it is in $log"
    grep -q ', 0 stale' "$log" || bad=1
    grep -qE ', 0 wrong answer, 0 crashed, 0 timed out, 0 did not build' "$log" || bad=1
  done
done

exit $bad
