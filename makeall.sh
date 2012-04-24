#!/bin/bash

make clean
rm Makefile *.pro
qmake -project
qmake
make clean
make
