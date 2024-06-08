cmake_minimum_required(VERSION 3.28)
project(chess_plusplus)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess_plusplus src/main.cpp
        src/Board.cpp)
