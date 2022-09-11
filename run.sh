#!/bin/bash
# Script to compile and execute a c api program
python3 setup.py build_ext --inplace
python3 setup.py install
cd ..
python3 test_spkmeans_lib/spkmeans.py 0 spk test_spkmeans_lib/input_1.txt
