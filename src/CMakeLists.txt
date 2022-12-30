cmake_minimum_required(VERSION 3.18)

add_library(DISP GraphicsHandler.cpp Image.cpp RgbBuffer.cpp)

target_include_directories(DISP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# imgui contains glfw
target_link_libraries(DISP PUBLIC DISP_lib)
