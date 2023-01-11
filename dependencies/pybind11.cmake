
# find the correct python installation
find_package (Python COMPONENTS Interpreter Development)

FetchContent_Declare(
        pybind11
        GIT_REPOSITORY          https://github.com/pybind/pybind11.git
        GIT_TAG                 v2.10.3
        GIT_SHALLOW             TRUE
        GIT_SUBMODULES_RECURSE  FALSE
        GIT_PROGRESS            TRUE
        GIT_SUBMODULES          ""
)
FetchContent_MakeAvailable(pybind11)
