#/bin/sh

set -e

mkdir -p tmp

for file in src/*.cpp; do
  bn=$(basename $file)
  g++ $file -Wall -Wextra -Wpedantic -std=c++20 -c -o tmp/$bn.o
done

g++ tmp/*.o -o program

