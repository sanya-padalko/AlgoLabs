#!/bin/bash

if [[ ! -d "hash_table_res" ]]; then
    mkdir "hash_table_res"
fi

gcc hash_table_load.c hash_func.c hash_tables/*.c -o table_load
./table_load