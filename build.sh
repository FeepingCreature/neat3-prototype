#!/usr/bin/env bash
set -euo pipefail
TARGET=./build
function buildC () {
    gcc -Wall -Werror -Wno-unused-value -Wno-unused-variable $1 runtime.c -I. -o $2 -g
}
mkdir -p "$TARGET"
echo "Build bootstrap compiler."
buildC bootstrap.c "$TARGET"/bootstrap
echo "Run bootstrap compiler."
"$TARGET"/bootstrap main.n3 "$TARGET"/main1.c
buildC "$TARGET"/main1.c "$TARGET"/main1
echo "Run main1 compiler."
"$TARGET"/main1 main.n3 "$TARGET"/main2.c
buildC "$TARGET"/main2.c "$TARGET"/main2
diff -ur "$TARGET"/main1.c "$TARGET"/main2.c
echo "Run main2 compiler."
"$TARGET"/main2 fibonacci.n3 "$TARGET"/fibonacci.c
buildC "$TARGET"/fibonacci.c "$TARGET"/fibonacci
echo "Run user program."
"$TARGET"/fibonacci
