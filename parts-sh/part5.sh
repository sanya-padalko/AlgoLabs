#!/bin/bash

( [[ -d "part5" ]] || mkdir part5 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 5
cd part5
python3 ../plot-gens/part5-plot.py
cd ..

find "part5" -maxdepth 1 -type f ! -iname "*.png" -delete
