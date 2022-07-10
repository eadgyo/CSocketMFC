#!/bin/bash
DIRNAME=$(dirname $0)
cd $DIRNAME
export LD_LIBRARY_PATH=$DIRNAME:$DIRNAME/..
java -Djava.library.path=. MainJNI
