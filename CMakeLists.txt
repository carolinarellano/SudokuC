cmake_minimum_required(VERSION 3.22)
project(SudokuC C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(SudokuC
        main.c
        sudoku.c
        sudoku.h)
