CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(arcade_nibbler SHARED nibbler.cpp)

target_include_directories(arcade_nibbler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(arcade_nibbler PROPERTIES PREFIX "")
add_custom_command(TARGET arcade_nibbler POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:arcade_nibbler>
        ${PROJECT_SOURCE_DIR}/lib/$<TARGET_FILE_NAME:arcade_nibbler>)