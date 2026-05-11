#!/bin/bash

if [[ ! -d "table_tests" ]]; then
    mkdir table_tests
fi

python3 table_test.py
echo "Tests generated"
gcc table_test.c hash_func.c hash_tables/*.c -o table_test
./table_test
python3 table_plot_1.py
python3 table_plot_2.py
