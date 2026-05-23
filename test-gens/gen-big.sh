#!/bin/bash

./test-gen-utils/test-gen.sh 0 1000000 10000
rm -rf big_tests
cp -r tests big_tests
rm -rf tests
