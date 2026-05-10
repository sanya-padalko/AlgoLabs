#!/bin/bash

echo -e "--- Part 7 is starting...\n"

mkdir -p results
gcc tester.c skiplist.c -o part7
echo -e "--- Tester's compilation ended\n"

./part7
rm part7
echo -e "--- Tests done\n"

python3 calc.py
echo -e "\n--- Results counted\n"

echo -e "--- Part 7 is ended."