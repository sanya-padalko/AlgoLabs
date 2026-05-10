#!/bin/bash

echo -e "--- Part 5 is starting...\n"

mkdir -p results
gcc tester.c rbtree.c -o part5
echo -e "--- Tester's compilation ended\n"

./part5
rm part5
echo -e "--- Tests done\n"

python3 calc.py
echo -e "\n--- Results counted\n"

echo -e "--- Part 5 is ended."