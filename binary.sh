#!/bin/bash

( [[ -d "binary" ]] || mkdir binary )

gcc tester.c -o tester.o
./tester.o 1
python3 binary-plot-gen.py