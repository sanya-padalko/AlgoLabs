#!/bin/bash

./test-gen-utils/test-gen.sh 0 1000000 10000
rm -rf test_most_dublicates
cp -r tests test_most_dublicates
rm -rf tests
