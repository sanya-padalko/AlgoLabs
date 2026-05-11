#!/bin/bash

mkdir -p results

./test-gen.sh
gcc hash_func.c -o hash_func
./hash_func