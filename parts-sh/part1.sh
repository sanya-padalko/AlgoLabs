#!/bin/bash

( [[ -d "part1" ]] || mkdir part1 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-small.sh
fi

gcc tester.c -o tester
./tester 1
cd part1
python ../plot-gens/part1-plot.py
python ../plot-gens/part1-shell-plot.py
cd ..
