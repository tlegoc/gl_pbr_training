cmake_minimum_required(VERSION 3.27)
project(gl_pbr_training)

set(CMAKE_CXX_STANDARD 17)

add_executable(gl_pbr_training main.cpp)

add_subdirectory(src)

# SDL2
if (UNIX AND NOT APPLE)
    message("-- Building on linux, using find_package")

    find_package(SDL2 REQUIRED)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    if (${SDL2_FOUND})
        message("-- SDL2 Found")
        include_directories(${SDL2_INCLUDE_DIRS})
        target_link_libraries(gl_pbr_training PUBLIC ${SDL2_LIBRARIES} Threads::Threads)
    else ()
        message("-- SDL2 Not found, downloading")
        add_compile_definitions(SDL2_GIT)
        add_subdirectory(thirdparty/SDL)
        target_link_libraries(gl_pbr_training PUBLIC SDL2 Threads::Threads)
    endif ()
elseif (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    message("-- Building on windows, downloading SDL2")
    add_compile_definitions(SDL2_GIT)
    add_subdirectory(thirdparty/SDL)
    target_link_libraries(gl_pbr_training PUBLIC SDL2-static)
endif ()


add_subdirectory(thirdparty/GLM)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(gl_pbr_training PUBLIC OpenGL::GL OpenGL::GLU glm ${GLEW_LIBRARIES})

# Set output directory
set_target_properties(gl_pbr_training PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_command(TARGET gl_pbr_training POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:gl_pbr_training>/shaders)

add_custom_command(TARGET gl_pbr_training POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:gl_pbr_training>/assets)