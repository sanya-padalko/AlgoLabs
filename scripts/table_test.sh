#!/bin/bash

mkdir -p table_tests

./scripts/test_gen.sh
python3 scripts_py/table_test.py
echo "Tests generated"
gcc -DLOAD_TEST table_test.c hash_func.c hash_tables/*.c -o table_test
./table_test
python3 scripts_py/table_plot_1.py
python3 scripts_py/table_plot_2.py
