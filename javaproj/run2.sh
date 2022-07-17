#!/bin/bash
DIRNAME=$(dirname $0)
cd $DIRNAME
export LD_LIBRARY_PATH=$DIRNAME:$DIRNAME/..:$DIRNAME/structs/:
java -Djava.library.path=. MainJNI2 | tee test.txt
