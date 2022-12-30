cmake_minimum_required(VERSION 3.19)
project(playground)

# in a normal project we would use
# add_subdirectory(disp/)
# this is not required because we are part of the directory

# add the source files
add_executable(playground Playground.cpp)

# for MacOS: build an app
set_target_properties(playground PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "DISP-Playground")

# add DISP as library dependency
target_link_libraries(playground DISP)

add_custom_command(TARGET playground POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)
