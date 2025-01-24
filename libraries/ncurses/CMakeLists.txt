CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(Curses REQUIRED)
add_library(arcade_ncurses SHARED ncurses.cpp ncurses.cpp)

target_include_directories(arcade_ncurses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(arcade_ncurses ${CURSES_LIBRARIES})
target_link_libraries(arcade_ncurses m)

set_target_properties(arcade_ncurses PROPERTIES PREFIX "")
add_custom_command(TARGET arcade_ncurses POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:arcade_ncurses>
        ${PROJECT_SOURCE_DIR}/lib/$<TARGET_FILE_NAME:arcade_ncurses>)