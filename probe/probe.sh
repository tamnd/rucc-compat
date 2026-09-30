#!/bin/sh
# Temporary: says which intrinsics in each failing program disagree, and what they return.
opt=$1; cc=$2; rucc=$3
cd corpus/intrinsics/neon
for f in *.c; do
  $cc -O$opt $f -o /tmp/g.out 2>/dev/null || { echo "gcc cannot build $f"; continue; }
  $rucc -O$opt $f -o /tmp/r.out 2>/tmp/r.err || { echo "rucc cannot build $f"; head -3 /tmp/r.err; continue; }
  /tmp/g.out > /tmp/g.txt; /tmp/r.out > /tmp/r.txt
  diff /tmp/g.txt /tmp/r.txt | grep '^<' | sed "s|^< sum \([a-z0-9_]*\) .*|DIFF $f \1|"
done
cd ../../../probe
$cc -O$opt probe.c -o /tmp/pg && /tmp/pg > /tmp/pg.txt
$rucc -O$opt probe.c -o /tmp/pr && /tmp/pr > /tmp/pr.txt
paste -d'|' /tmp/pg.txt /tmp/pr.txt | sed 's/|/   RUCC: /'
$rucc -O$opt -S ../corpus/intrinsics/acle-flagged/crc32.c -march=armv8-a+crc+simd -I../corpus/intrinsics -o /tmp/r.s && grep -n '\.arch\|crc32c\?b' /tmp/r.s | head -5
$cc -O$opt -S ../corpus/intrinsics/acle-flagged/crc32.c -march=armv8-a+crc+simd -o /tmp/g.s && grep -n '\.arch\|crc32c\?b' /tmp/g.s | head -5
$cc -O$opt -S ../corpus/intrinsics/acle-attribute/crc32.c -o /tmp/g2.s && grep -n '\.arch\|crc32b' /tmp/g2.s | head -5
