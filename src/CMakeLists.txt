cmake_minimum_required(VERSION 3.18)

set(DISP_src
  "GraphicsHandler.cpp"
  CACHE STRING "All source files of DISP"
)

add_library(DISP ${DISP_src})

target_include_directories(DISP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# imgui contains glfw
target_link_libraries(DISP PUBLIC imgui implot glad)
