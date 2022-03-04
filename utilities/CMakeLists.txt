cmake_minimum_required(VERSION 3.19)
project(Utilities)

set(CMAKE_CXX_STANDARD 14)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/utilities)

add_library(Utilities utilities.cpp)