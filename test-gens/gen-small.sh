#!/bin/bash

./test-gen-utils/test-gen.sh 0 1000 50
rm -rf small_tests
cp -r tests small_tests
rm -rf tests
