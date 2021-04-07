#!/bin/bash

./ifcc test.s > test.s
as -o test.o test.s
gcc test.o
./a.out
echo $?

