#!/usr/bin/env bash
set -euo pipefail
TARGET=./build
mkdir -p "$TARGET"
echo "Build bootstrap compiler."
gcc bootstrap.c runtime.c -I. -o "$TARGET"/bootstrap -g
echo "Run bootstrap compiler."
"$TARGET"/bootstrap main.n3 "$TARGET"/main1.c
gcc "$TARGET"/main1.c runtime.c -I. -o "$TARGET"/main1 -g
echo "Run main1 compiler."
"$TARGET"/main1 main.n3 "$TARGET"/main2.c
gcc "$TARGET"/main2.c runtime.c -I. -o "$TARGET"/main2 -g
diff -ur "$TARGET"/main1.c "$TARGET"/main2.c
echo "Run main2 compiler."
"$TARGET"/main2 fibonacci.n3 "$TARGET"/fibonacci.c
gcc "$TARGET"/fibonacci.c runtime.c -I. -o "$TARGET"/fibonacci
echo "Run user program."
"$TARGET"/fibonacci
