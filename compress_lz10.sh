#!/bin/sh
infile="$1"
outfile="data/$(basename "$infile" .bin)_lz10.bin"
gbalzss e "$infile" "$outfile" 
