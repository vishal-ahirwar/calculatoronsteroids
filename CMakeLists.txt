#Auto Generated Root CMake file by Flick CLI
#Copyright(c) 2025 None.All rights reerved.
cmake_minimum_required(VERSION 3.6...3.31)
project(calculatoronsteroids VERSION 1.0.0 LANGUAGES CXX)
include(cmake/config.cmake)
#@add_find_package Warning: Do not remove this line
find_path(BARKEEP_INCLUDE_DIRS "barkeep/barkeep.h")
find_package(Boost REQUIRED COMPONENTS multiprecision)

#@add_subproject Warning: Do not remove this line
add_subdirectory(calculatoronsteroids)
