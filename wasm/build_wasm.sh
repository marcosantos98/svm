#!/bin/sh

set -xe

emcc -x c ../src/main.c ../src/parser.c ../src/svm.c ../src/inst.c -o svm
