#!/bin/bash

if [[ ! -d "hash_table_res" ]]; then
    mkdir hash_table_res
fi

./test_load.sh
python3 table_load_plot.py