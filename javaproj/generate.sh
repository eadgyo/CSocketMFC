#!/bin/bash
cd $(dirname $0)
./generate_struct.sh
cd ./structs/
javac -cp . T_TEST_1.java
javac -cp . T_TEST_2.java
