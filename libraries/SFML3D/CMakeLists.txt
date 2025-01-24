CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(SFML COMPONENTS system window graphics REQUIRED)

add_library(arcade_SFML3D SHARED sfml3d.cpp)

target_include_directories(arcade_SFML3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(arcade_SFML3D sfml-graphics sfml-window sfml-system)

set_target_properties(arcade_SFML3D PROPERTIES PREFIX "")
add_custom_command(TARGET arcade_SFML3D POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:arcade_SFML3D>
        ${PROJECT_SOURCE_DIR}/lib/$<TARGET_FILE_NAME:arcade_SFML3D>)