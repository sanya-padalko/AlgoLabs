#!/bin/bash

( [[ -d "part10" ]] || mkdir part10 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester
cd part10
python ../plot-gens/part10-plot.py
cd ..
