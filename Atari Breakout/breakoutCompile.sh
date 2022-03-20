#!/bin/sh
# Use this for compiling with seperate compilation (multiple header and C++ files)
g++ -std=c++11 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a breakout.cpp ./implementation/Ball.cpp ./implementation/Game.cpp ./implementation/Paddle.cpp ./implementation/TileManager.cpp -o breakout