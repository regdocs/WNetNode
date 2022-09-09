#!/bin/bash

cd applet && qmake && make
cd .. && cd acorn
g++ main.cc -o ../build/acorn-cmd
