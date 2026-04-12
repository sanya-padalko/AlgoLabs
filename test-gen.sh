#!/bin/bash

if [[ ! -d "tests" ]]; then
    mkdir tests
fi

cd tests

python3 ../test-gen.py

cd ..