#!/bin/bash

( [[ -d "part6" ]] || mkdir part6 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 6
cd part6
python ../plot-gens/part6-plot.py
cd ..
