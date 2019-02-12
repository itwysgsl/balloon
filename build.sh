#!/bin/bash
cd "$(dirname "$0")" || exit 1

gcc -c sphlib/sph_groestl.c
gcc -c balloon.c

g++ -std=c++11 ./main.cpp -o balloon_hash sph_groestl.o balloon.o