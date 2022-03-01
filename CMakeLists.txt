cmake_minimum_required(VERSION 3.19)
project(CPP_learn)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)



add_executable(Stack Stack.cpp)

add_executable(maintest maintest.cpp Stack.cpp)


