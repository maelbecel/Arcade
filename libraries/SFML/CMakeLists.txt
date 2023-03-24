CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(SFML COMPONENTS system window graphics REQUIRED)

add_library(arcade_SFML SHARED sfml.cpp)

target_include_directories(arcade_SFML PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(arcade_SFML sfml-graphics sfml-window sfml-system)