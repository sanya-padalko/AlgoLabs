#!/bin/bash

( [[ -d "part7" ]] || mkdir part7 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c -o tester
./tester 7
cd part7
python ../plot-gens/part7-coef-plot.py
python ../plot-gens/part7-intro-plot.py
cd ..
