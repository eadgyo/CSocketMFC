#!/bin/bash
cd $(dirname $0)
rm -rf ./structs
mkdir ./structs
python3 ./generate_struct.py ../include/structures.h
