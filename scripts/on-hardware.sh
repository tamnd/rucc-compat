#!/bin/sh
# Runs the whole harness on real machines rather than on a runner in a container.
#
# The reason this exists is the last box of tamnd/rucc#260. Everything CI does runs on a fresh
# Ubuntu image with one libc, one linker and one gcc, and the two things most likely to be wrong
# about a compiler nobody else has run are the ABI and the link. A machine somebody actually uses
# has a different distribution, a different gcc, a different default for whether a link makes a
# position independent executable, and headers the runner image does not have, and none of that
# is visible until the suites are run there. `execute/pr54937.c` is the case that made the point:
# it failed on one machine and passed on another with the same compiler version, because the two
# gccs were built with different answers to that last question.
#
# It drives ssh rather than installing anything. No agent runs on the far side, nothing listens,
# and the machines are named nowhere in this repository: the host list comes from the environment
# or from a file outside the tree, and the reports it writes land under results/, which is
# ignored. That is the reason this is a script here rather than a matrix of self hosted runners
# in the workflow, where the labels would have to be written down in public.
#
# Usage:
#
#   RUCC_COMPAT_HOSTS="one two three" ./scripts/on-hardware.sh
#   RUCC_COMPAT_HOSTS_FILE=~/notes/hosts ./scripts/on-hardware.sh
#
# A host is anything ssh takes, so an alias out of ~/.ssh/config is the usual answer and keeps
# the addresses off the command line as well.
#
# The knobs, all optional:
#
#   RUCC_COMPAT_RUCC     the compiler checkout to send, default ../rucc next to this one
#   RUCC_COMPAT_LEVELS   the optimization levels to run, default all six
#   RUCC_COMPAT_CC       the reference compiler on the far side, default worked out per host
#   RUCC_COMPAT_REMOTE   the directory to work in on the far side, default rucc-hardware
#   RUCC_COMPAT_KEEP     set to 1 to leave the remote trees in place for a later run
#
# It exits non zero if any machine did, and it does not stop at the first one: a run that gives
# up on the first red machine tells you about one machine when you asked about four.

set -eu

here=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
rucc=${RUCC_COMPAT_RUCC:-$(dirname -- "$here")/rucc}
levels=${RUCC_COMPAT_LEVELS:-"0 1 2 3 s z"}
remote=${RUCC_COMPAT_REMOTE:-rucc-hardware}
cc=${RUCC_COMPAT_CC:-}

if [ -n "${RUCC_COMPAT_HOSTS_FILE:-}" ]; then
  hosts=$(sed -e 's/#.*//' "$RUCC_COMPAT_HOSTS_FILE")
else
  hosts=${RUCC_COMPAT_HOSTS:-}
fi

if [ -z "$(printf '%s' "$hosts" | tr -d '[:space:]')" ]; then
  echo "on-hardware: no hosts. Set RUCC_COMPAT_HOSTS or RUCC_COMPAT_HOSTS_FILE." >&2
  echo "on-hardware: the names are yours and they stay out of this repository." >&2
  exit 2
fi

if [ ! -f "$rucc/Cargo.toml" ]; then
  echo "on-hardware: no compiler checkout at $rucc. Set RUCC_COMPAT_RUCC." >&2
  exit 2
fi

# One directory per host under results/, so two machines disagreeing is two files to diff rather
# than one file whichever ran last.
mkdir -p "$here/results/hardware"

failed=""
for host in $hosts; do
  echo
  echo "== $host"

  # rsync makes the last directory of a path and not the ones above it, so the two trees are made
  # here first. This is also the first thing that talks to the machine, so a host that is not
  # reachable says so before anything large is copied.
  ssh "$host" "mkdir -p '$remote/compat' '$remote/rucc'"

  # Both trees go over, because the compiler is what is being measured and building it there
  # rather than shipping a binary is what makes the answer about that machine. target and .git
  # are excluded because they are large and neither is wanted on the far side, and vendor is
  # excluded because the corpora are fetched there from their own manifests.
  rsync -a --delete --exclude target --exclude .git --exclude vendor \
    "$here/" "$host:$remote/compat/"
  rsync -a --delete --exclude target --exclude .git \
    "$rucc/" "$host:$remote/rucc/"

  # The far half is a file in the tree that was just copied over rather than a string built here,
  # so that the quoting is a shell script somebody can read and run by hand on the machine when
  # it goes red. Everything it needs is in the environment, which ssh does not forward, so it is
  # set on the command line instead.
  if ssh "$host" \
    "ON_HARDWARE_ROOT='$remote' ON_HARDWARE_LEVELS='$levels' ON_HARDWARE_CC='$cc' \
     sh '$remote/compat/scripts/on-hardware-remote.sh'"; then
    echo "== $host green"
  else
    echo "== $host red"
    failed="$failed $host"
  fi

  # The reports come back whichever way it went, because a red run is the one worth reading.
  mkdir -p "$here/results/hardware/$host"
  rsync -a "$host:$remote/compat/results/" "$here/results/hardware/$host/" || true

  if [ "${RUCC_COMPAT_KEEP:-}" != "1" ]; then
    ssh "$host" "rm -rf '$remote'" || true
  fi
done

echo
if [ -n "$failed" ]; then
  echo "on-hardware: red on$failed"
  exit 1
fi
echo "on-hardware: green everywhere"
