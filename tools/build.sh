#!/bin/sh

mkdir -p bin

gcc -std=c23 countletters.c -o bin/countletters
g++ -std=c++20 duplicates.cpp -o bin/duplicates

