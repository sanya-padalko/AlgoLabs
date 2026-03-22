#!/bin/bash

( [[ -d "part4" ]] || mkdir part4 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
	./test-gens/gen-dub.sh
fi

gcc tester.c -o tester
./tester 4
cd part4
python ../plot-gens/part4-plot.py
python ../plot-gens/part4-dub-plot.py
cd ..
