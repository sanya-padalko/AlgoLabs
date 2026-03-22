#!/bin/bash

if [[ $# -ne 3 ]]; then
    echo "Wrong arguments count, expected: from, to, step"
    exit 1
fi

rm -rf tests

mkdir "tests" && cd "tests"

if [[ -d "tests" ]]; then
    echo "Directory for tests didn't create"
    exit 1
fi

py_name="test-gen"
c_name="test-sort"

from=$1
to=$2
step=$3

max_value=10000

gcc ../test-gen-utils/${c_name}.c -o ${c_name}

for (( size=from; size <= to; size += step )); do
    for (( ind=1; ind <= 5; ind++ )); do
        cur_test=""
        cur_test=$(python3 "../test-gen-utils/${py_name}.py" "$size" "$max_value")
        echo "$cur_test" >> ${size}_${ind}.in
        echo "$cur_test" | "./${c_name}" >> ${size}_${ind}.out
    done
    echo -ne "Progress: $size/$to               \r"
done
echo
