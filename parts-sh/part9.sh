#!/bin/bash

( [[ -d "part9" ]] || mkdir part9 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 9
cd part9
python ../plot-gens/part9-plot.py
cd ..

find "part9" -maxdepth 1 -type f ! -iname "*.png" -delete
