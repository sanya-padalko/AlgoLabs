#!/bin/bash

mkdir -p plots

python3 hash_func_plots/plot_int.py
echo
python3 hash_func_plots/plot_float.py
echo
python3 hash_func_plots/plot_string.py