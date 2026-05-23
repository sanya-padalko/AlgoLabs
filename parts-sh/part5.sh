#!/bin/bash

( [[ -d "part5" ]] || mkdir part5 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 5

if [[ -d ".venv" ]]; then
	source .venv/bin/activate
else
	python3 -m venv .venv
	source .venv/bin/activate
fi

pip install matplotlib

cd part5
python3 ../plot-gens/part5-plot.py
cd ..

deactivate

find "part5" -maxdepth 1 -type f ! -iname "*.png" -delete
