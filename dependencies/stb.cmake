FetchContent_Declare(
stb
GIT_REPOSITORY          https://github.com/nothings/stb.git
GIT_SHALLOW TRUE
GIT_SUBMODULES_RECURSE  FALSE
GIT_PROGRESS            TRUE
GIT_SUBMODULES          ""
)

FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
FetchContent_Populate(stb) # does not include cmake
endif()

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
