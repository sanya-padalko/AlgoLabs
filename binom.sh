#!/bin/bash

( [[ -d "binomial" ]] || mkdir binomial )

gcc tester.c -o tester.o
./tester.o 2
python3 binom-plot-gen.py