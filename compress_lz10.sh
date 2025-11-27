#!/bin/sh
infile="$1"
outfile="data/$(basename "$infile" .bin)_lz10.bin"
if [ ! -f "$outfile" ] || [ "$infile" -nt "$outfile" ]; then
    gbalzss e "$infile" "$outfile"
    echo -n "C"
else
  echo -n "S"
fi

