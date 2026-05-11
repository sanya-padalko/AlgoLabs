#!/bin/bash

mkdir -p hash_table_res

./scripts/test_load.sh
python3 scripts_py/table_load_plot.py