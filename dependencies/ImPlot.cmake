include(FetchContent)

FetchContent_Declare(
        implot
        GIT_REPOSITORY          https://github.com/epezent/implot.git
        GIT_TAG                 626e391670a4018a365787e35ef4cf01cb68ee31
        #GIT_SHALLOW TRUE
        GIT_SUBMODULES_RECURSE  FALSE
        GIT_PROGRESS            TRUE
        GIT_SUBMODULES          ""
)

FetchContent_GetProperties(implot)
if(NOT implot_POPULATED)
    FetchContent_Populate(implot) # does not include cmake
endif()

add_library(implot
        ${implot_SOURCE_DIR}/implot.cpp
        ${implot_SOURCE_DIR}/implot_demo.cpp
        ${implot_SOURCE_DIR}/implot_items.cpp
        )
target_link_libraries(implot PUBLIC imgui)
target_include_directories(implot PUBLIC ${implot_SOURCE_DIR})
