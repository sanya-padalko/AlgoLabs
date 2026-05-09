#!/bin/bash

echo -e "--- Part 2 is starting...\n"

mkdir -p results
gcc tester.c avl.c -o part2
echo -e "--- Tester's compilation ended\n"

./part2
rm part2
echo -e "--- Tests done\n"

python3 calc.py
echo -e "\n--- Results counted\n"

echo -e "--- Part2 is ended."