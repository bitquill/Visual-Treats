#!/bin/sh
# Use this for compiling for one single C++ file!!
g++ -std=c++11 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a $1.cpp -o $1