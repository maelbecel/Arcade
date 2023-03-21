CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(arcade_libtest SHARED test.cpp)

target_include_directories(arcade_libtest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})