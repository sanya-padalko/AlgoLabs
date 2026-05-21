#!/bin/bash

( [[ -d "part6" ]] || mkdir part6 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 6
cd part6
python3 ../plot-gens/part6-plot.py
cd ..

find "part6" -maxdepth 1 -type f ! -iname "*.png" -delete
