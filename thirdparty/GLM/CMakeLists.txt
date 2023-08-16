
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        GLM
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 0.9.9.8
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(GLM)