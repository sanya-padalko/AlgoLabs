#!/bin/bash

if [[ ! -d "results" ]]; then
    mkdir results
fi

./test-gen.sh
gcc hash_func.c -o hash_func
./hash_func