include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY  https://github.com/libsdl-org/SDL
        GIT_TAG         release-2.26.5
        GIT_PROGRESS    TRUE
)

FetchContent_MakeAvailable(SDL2)