cmake_minimum_required(VERSION 3.19)
project(testSFML VERSION 1.0)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(lib.h SHARED IMPORTED)
add_library(grid.h SHARED IMPORTED)
add_library(board_handler.h SHARED IMPORTED)
add_library(sfml_text.h SHARED IMPORTED)

add_executable(
        MineSweeperSFML
        main.cpp
)
target_link_libraries(
        MineSweeperSFML
        sfml-graphics
)