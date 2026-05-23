#!/bin/bash

( [[ -d "part7" ]] || mkdir part7 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 7

if [[ -d ".venv" ]]; then
	source .venv/bin/activate
else
	python3 -m venv .venv
	source .venv/bin/activate
fi

pip install matplotlib

cd part7
python3 ../plot-gens/part7-coef-plot.py
python3 ../plot-gens/part7-intro-plot.py
cd ..

deactivate

find "part7" -maxdepth 1 -type f ! -iname "*.png" -delete
