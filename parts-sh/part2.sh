#!/bin/bash

( [[ -d "part2" ]] || mkdir part2 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c -o tester
./tester 2
cd part2
python ../plot-gens/part2-plot.py
cd ..
