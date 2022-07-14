#!/bin/bash
cd $(dirname $0)
python3 generate_native.py JNITest test_jni ../include/Test.h
