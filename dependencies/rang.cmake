FetchContent_Declare(
        rang
        GIT_REPOSITORY          https://github.com/agauniyal/rang.git
        GIT_TAG                 v3.2
        GIT_SHALLOW             TRUE
        GIT_SUBMODULES_RECURSE  FALSE
        GIT_PROGRESS            TRUE
        GIT_SUBMODULES          ""
)
FetchContent_MakeAvailable(rang)