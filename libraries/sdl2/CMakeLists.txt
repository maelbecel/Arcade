CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)

add_library(arcade_sdl2 SHARED sdl2.cpp)

target_include_directories(arcade_sdl2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(arcade_sdl2 ${SDL2_LIBRARIES} -lSDL2_ttf -lSDL2_image)

set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
add_custom_command(TARGET arcade_sdl2 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:arcade_sdl2>
        ${PROJECT_SOURCE_DIR}/lib/$<TARGET_FILE_NAME:arcade_sdl2>)