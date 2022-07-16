#!/bin/bash
if [ -z "$1" ]; then
    ./generate_cpp.sh
fi
make all2
make all3
cp result.so libresult.so
javac MainJNI2.java
