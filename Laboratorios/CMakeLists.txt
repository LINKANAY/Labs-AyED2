cmake_minimum_required(VERSION 3.28)
project(Laboratorios)

set(CMAKE_CXX_STANDARD 14)

include_directories("Lab 4/ej7")

add_executable(Laboratorios
        "Lab 4/ej7/input/all-negative-100.in"
        "Lab 4/ej7/input/all-positive-100.in"
        "Lab 4/ej7/input/empty.in"
        "Lab 4/ej7/input/example-sorted.in"
        "Lab 4/ej7/input/example-unsorted.in"
        "Lab 4/ej7/array_helpers.c"
        "Lab 4/ej7/array_helpers.h"
        "Lab 4/ej7/list.c"
        "Lab 4/ej7/list.h"
        "Lab 4/ej7/main.c")
