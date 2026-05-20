#!/bin/bash

mkdir -p results
gcc tester.c bst.c -o part1
echo "Tester compilated"

./part1
rm part1
echo "Tests done"

python3 calc.py
echo "Results counted"