﻿cmake_minimum_required(VERSION 3.19)
project(CPP_learn)

add_subdirectory(algorithms)
add_subdirectory(utilities)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/include)



add_executable(maintest maintest.cpp)


