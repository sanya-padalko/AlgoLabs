#!/bin/bash

( [[ -d "part6" ]] || mkdir part6 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 6

if [[ -d ".venv" ]]; then
	source .venv/bin/activate
else
	python3 -m venv .venv
	source .venv/bin/activate
fi

pip install matplotlib

cd part6
python3 ../plot-gens/part6-plot.py
cd ..

deactivate

find "part6" -maxdepth 1 -type f ! -iname "*.png" -delete
