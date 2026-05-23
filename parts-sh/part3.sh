#!/bin/bash

( [[ -d "part3" ]] || mkdir part3 )

if [[ $# -ne 2 ]] && [[ "$1" = "-g" ]]; then
	./test-gens/gen-big.sh
fi

gcc tester.c src/*.c -o tester -Iinc
./tester 3

if [[ -d ".venv" ]]; then
	source .venv/bin/activate
else
	python3 -m venv .venv
	source .venv/bin/activate
fi

pip install matplotlib

cd part3
python3 ../plot-gens/part3-plot.py
cd ..

deactivate

find "part3" -maxdepth 1 -type f ! -iname "*.png" -delete
