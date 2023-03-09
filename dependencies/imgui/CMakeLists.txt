cmake_minimum_required(VERSION 3.12...3.23)

include(FetchContent)

# download imgui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY          https://github.com/ocornut/imgui.git
  GIT_TAG                 e2cede6542d2d6c83598d4d34dc51de84aeb282f
  #GIT_SHALLOW            TRUE
  GIT_SUBMODULES_RECURSE  FALSE
  GIT_PROGRESS            TRUE
  GIT_SUBMODULES          ""
)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
  FetchContent_Populate(imgui) # does not include cmake
endif()

# get source directory
set(IMGUI_DIR ${imgui_SOURCE_DIR})

# add opengl backend
add_library(imgui_backend ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)
target_include_directories(imgui_backend PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends ${CMAKE_CURRENT_SOURCE_DIR})

# link glfw
# TODO: do we need ${GLFW_STATIC_LIBRARIES}???
target_link_libraries(imgui_backend PUBLIC glad glfw ${GLFW_STATIC_LIBRARIES})

if(APPLE)
  message(STATUS "Using OpenGL on MacOS")
  # supress deprecation messages
  target_compile_definitions(imgui_backend PUBLIC GL_SILENCE_DEPRECATION)
endif()


# add global compile definition for imgui settings
# all other targets will have to include this (including imgui itself)
target_compile_definitions(imgui_backend PUBLIC IMGUI_USER_CONFIG="imconfig_custom.h" IMGUI_DEFINE_MATH_OPERATORS)

# disable backend specific includes for all top project
# we will use glad as OpenGL loader
target_compile_definitions(imgui_backend PUBLIC GLFW_INCLUDE_NONE)

# add imgui sources including freetype for fonts and stdlib support
add_library(imgui
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp

  ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)


# this is not necessary because imgui_backend includes these
# but for completion, we include these headers again
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/misc/cpp ${CMAKE_CURRENT_SOURCE_DIR})

# link freetype and the selected backend
target_link_libraries(imgui PUBLIC imgui_backend)
