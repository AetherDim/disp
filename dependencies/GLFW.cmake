#
# GLFW
#
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY          https://github.com/glfw/glfw.git
        GIT_TAG                 3.3.8
        GIT_SHALLOW             TRUE
        GIT_SUBMODULES_RECURSE  FALSE
        GIT_PROGRESS            TRUE
        GIT_SUBMODULES          ""
)
FetchContent_MakeAvailable(glfw)
