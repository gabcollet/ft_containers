#!/bin/bash

# Verification for 2 arguments 
# if [ "$#" -ne 2 ]; then
#     echo "Need 2 parameters, got $#"
#     exit 1
# fi

# Create variables
cppdir="tests"
objdir="obj"
outdir="tests/output"
incdir="includes/"
errlog="err.log"
flags='-Wall -Werror -Wextra -std=c++98'

# src_file_path="$PWD/$1"
# run_file_path="$PWD/a.out"
# in_file_path="$PWD/$2"

# Remove the old dir
if [ -d "$outdir" ]; then
    rm -rf $outdir
fi

# compile
mkdir -p "$outdir"
for f in "$cppdir"/*; do
    b=$(basename "${f%.cpp}")
    printf '%s\n' "$b" >> "$errlog"
    clang++ "$f" $flags -I"$incdir" -o "$outdir/$b.out" 2> "$errlog"
done



# clang++ $src_file_path -o $run_file_path -std=c++98 -Wall -Wextra -Werror

# run
# $run_file_path < $in_file_path