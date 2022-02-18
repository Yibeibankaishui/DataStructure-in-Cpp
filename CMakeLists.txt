cmake_minimum_required(VERSION 3.19)
project(CPP_learn)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CPP_learn
        algorithms/PostfixNotation.cpp
        algorithms/SymbolBalance.cpp
        ADT_list.cpp
        big_five_test.cpp
        copy_test.cpp
        List.h
        maintest.cpp
        Queue.h
        Stack.h
        Vector.h)
