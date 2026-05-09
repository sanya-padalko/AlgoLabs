#!/bin/bash

echo -e "--- Part 3 is starting...\n"

mkdir -p results
gcc tester.c treap.c -o part3
echo -e "--- Tester's compilation ended\n"

./part3
rm part3
echo -e "--- Tests done\n"

python3 calc.py
echo -e "\n--- Results counted\n"

echo -e "--- Part3 is ended."