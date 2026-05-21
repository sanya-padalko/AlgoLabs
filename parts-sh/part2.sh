#!/bin/bash

( [[ -d "part2" ]] || mkdir part2 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 2
cd part2
python3 ../plot-gens/part2-plot.py
cd ..

find "part2" -maxdepth 1 -type f ! -iname "*.png" -delete
