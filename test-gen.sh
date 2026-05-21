#!/bin/bash

( [[ -d "tests" ]] || mkdir tests )

gcc test-gen.c -o tests/test-gen.o
./tests/test-gen.o