cmake_minimum_required(VERSION 3.19)
project(algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(../utilities)
include_directories(..)

# message(STATUS ${PROJECT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/algorithms)

add_executable(PostfixNotation PostfixNotation.cpp)
target_link_libraries(PostfixNotation Utilities)

add_executable(InfixToPostfix InfixToPostfix.cpp)
target_link_libraries(InfixToPostfix Utilities)

add_executable(SymbolBalance SymbolBalance.cpp)