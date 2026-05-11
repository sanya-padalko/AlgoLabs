#!/bin/bash

mkdir -p "hash_table_res"

gcc hash_table_load.c hash_func.c hash_tables/*.c -o table_load
./table_load