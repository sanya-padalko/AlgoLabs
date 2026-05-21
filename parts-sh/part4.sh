#!/bin/bash

( [[ -d "part4" ]] || mkdir part4 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
	./test-gens/gen-dub.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 4
cd part4
python3 ../plot-gens/part4-plot.py
python3 ../plot-gens/part4-dub-plot.py
cd ..

find "part4" -maxdepth 1 -type f ! -iname "*.png" -delete
