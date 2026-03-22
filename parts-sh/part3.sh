#!/bin/bash

( [[ -d "part3" ]] || mkdir part3 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c -o tester
./tester 3
cd part3
python ../plot-gens/part3-plot.py
cd ..
