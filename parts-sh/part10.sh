#!/bin/bash

( [[ -d "part10" ]] || mkdir part10 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester
cd part10
python3 ../plot-gens/part10-plot.py
cd ..

find "part10" -maxdepth 1 -type f ! -iname "*.png" -delete
