cmake_minimum_required(VERSION 3.26)
project(TDA_Sudoku)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TDA_Sudoku
        Jaula.h
        Sudoku_killer.h)
