#!/bin/bash

( [[ -d "part9" ]] || mkdir part9 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 9

if [[ -d ".venv" ]]; then
	source .venv/bin/activate
else
	python3 -m venv .venv
	source .venv/bin/activate
fi

pip install matplotlib

cd part9
python3 ../plot-gens/part9-plot.py
cd ..

deactivate

find "part9" -maxdepth 1 -type f ! -iname "*.png" -delete
