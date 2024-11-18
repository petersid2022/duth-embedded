#!/bin/sh

set -xe

CC="gcc"
CFLAGS="-std=c99 -pedantic -Wall -Wextra -O0 -ggdb3 -fsanitize=address"
IFLAGS="-Isrc"
LFLAGS="-lm"
SRC="./src/file.c ./src/distance_transformer.c ./src/main.c"
OUTFILE="./transformer"

$CC $IFLAGS $CFLAGS -o $OUTFILE $SRC

$OUTFILE

rm $OUTFILE
