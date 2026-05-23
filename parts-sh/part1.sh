#!/bin/bash

( [[ -d "part1" ]] || mkdir part1 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-small.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 1

if [[ -d ".venv" ]]; then
	source .venv/bin/activate
else
	python3 -m venv .venv
	source .venv/bin/activate
fi

pip install matplotlib

cd part1
python3 ../plot-gens/part1-plot.py
python3 ../plot-gens/part1-shell-plot.py
cd ..

deactivate

find "part1" -maxdepth 1 -type f ! -iname "*.png" -delete
