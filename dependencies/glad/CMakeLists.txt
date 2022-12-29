cmake_minimum_required(VERSION 3.18)

project(glad)

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)

set_target_properties(glad PROPERTIES LANGUAGE C)
