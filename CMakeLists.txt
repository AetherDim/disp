cmake_minimum_required(VERSION 3.18)

project(DISP LANGUAGES CXX)

# export compile commands for IDE
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(examples)