#!/usr/bin/env bash
set -euo pipefail
TARGET=./build
mkdir -p "$TARGET"
DMD="$HOME"/dmd-2.105.0/linux/bin64/dmd
echo "Build bootstrap compiler."
"$DMD" bootstrap.d -unittest -of"$TARGET"/bootstrap -g
echo "Run bootstrap compiler."
"$TARGET"/bootstrap main.n3 "$TARGET"/main_.d
"$DMD" "$TARGET"/main_.d -i -of"$TARGET"/main -g
echo "Run main compiler."
"$TARGET"/main main.n3 "$TARGET"/main2_.d
"$DMD" "$TARGET"/main2_.d -i -of"$TARGET"/main2 -g
echo "Run main2 compiler."
"$TARGET"/main2 main.n3 "$TARGET"/main3_.d
"$DMD" "$TARGET"/main3_.d -i -of"$TARGET"/main3 -g
diff -ur "$TARGET"/main2_.d "$TARGET"/main3_.d
echo "Run main3 compiler."
"$TARGET"/main3 fibonacci.n3 "$TARGET"/fibonacci_.d
"$DMD" -i "$TARGET"/fibonacci_.d -of"$TARGET"/fibonacci
echo "Run user program."
"$TARGET"/fibonacci
