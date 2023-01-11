cmake_minimum_required(VERSION 3.18)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE) # enable git progress

add_library(DISP_lib INTERFACE)

# At the moment only OpenGL is supported for backend.

# 1. glad for opengl
add_subdirectory(glad)
# 2. glfw for window creation
include(GLFW.cmake)
# 3. imgui
add_subdirectory(imgui)

# glfw is included with imgui
target_link_libraries(DISP_lib INTERFACE imgui glad)

#
# include dependencies
#
option(DISP_dep_implot "include ImPlot in build (some examples require ImPlot)" ON)
if(DISP_dep_implot)
  include(ImPlot.cmake)
  target_link_libraries(DISP_lib INTERFACE implot)
endif()

option(DISP_stb "include stb in build" ON)
if(DISP_stb)
    include(stb.cmake)
    target_link_libraries(DISP_lib INTERFACE stb)
endif()

option(DISP_entt "include entt in build" OFF)
if(DISP_entt)
    include(entt.cmake)
    target_link_libraries(DISP_lib INTERFACE entt)
endif()

option(DISP_python "include python and pybind in build" OFF)
if(DISP_python)
    include(pybind11.cmake)
    target_link_libraries(DISP_lib INTERFACE pybind11::embed)
endif()

option(DISP_rang "include rang in build" OFF)
if(DISP_rang)
    include(rang.cmake)
    target_link_libraries(DISP_lib INTERFACE rang)
endif()