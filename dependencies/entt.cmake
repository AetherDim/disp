FetchContent_Declare(
        entt
        GIT_REPOSITORY          https://github.com/skypjack/entt.git
        GIT_TAG                 v3.11.1
        GIT_SHALLOW TRUE
        GIT_SUBMODULES_RECURSE  FALSE
        GIT_PROGRESS            TRUE
        GIT_SUBMODULES          ""
)

FetchContent_MakeAvailable(entt)
