#!/bin/bash

echo -e "--- Part 4 is starting...\n"

mkdir -p results
gcc tester.c splay.c -o part4
echo -e "--- Tester's compilation ended\n"

./part4
rm part4
echo -e "--- Tests done\n"

python3 calc.py
echo -e "\n--- Results counted\n"

echo -e "--- Part4 is ended."