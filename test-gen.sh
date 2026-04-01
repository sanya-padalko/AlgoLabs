#!/bin/bash

( [[ -d "tests" ]] || mkdir tests )
( [[ -d "binomial" ]] || mkdir binomial )

gcc test-gen.c -o tests/test-gen.o
./tests/test-gen.o