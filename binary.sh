#!/bin/bash

( [[ -d "binary" ]] || mkdir binary )

gcc tester.c binary-heap.c binom-heap.c -o tester.o
./tester.o 1
python3 binary-plot-gen.py