#!/bin/bash

( [[ -d "part9" ]] || mkdir part9 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c -o tester
./tester 9
cd part9
python ../plot-gens/part9-plot.py
cd ..
