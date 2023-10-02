cmake_minimum_required(VERSION 3.25)
project(gl_pbr_training)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(gl_pbr_training main.cpp)

add_subdirectory(src)

find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
set(Boost_NO_WARN_NEW_VERSIONS ON)
find_package(Boost REQUIRED COMPONENTS regex)
find_package(glm CONFIG REQUIRED)

target_link_libraries(gl_pbr_training
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        )

target_link_libraries(gl_pbr_training PRIVATE GLEW::GLEW Boost::regex glm::glm)

#if (UNIX AND NOT APPLE)
    add_custom_command(
            TARGET gl_pbr_training
            POST_BUILD COMMAND ${CMAKE_COMMAND}
            -E create_symlink ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/bin/shaders
            DEPENDS ${CMAKE_BINARY_DIR}/bin/shaders
    )

    add_custom_command(
            TARGET gl_pbr_training
            POST_BUILD COMMAND ${CMAKE_COMMAND}
            -E create_symlink ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets
            DEPENDS ${CMAKE_BINARY_DIR}/bin/assets
    )
#endif()

#if (WIN32)
#    add_custom_command(
#            TARGET gl_pbr_training
#            POST_BUILD COMMAND ${CMAKE_COMMAND}
#            -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/bin/shaders
#            DEPENDS ${CMAKE_BINARY_DIR}/bin/shaders
#    )
#
#    add_custom_command(
#            TARGET gl_pbr_training
#            POST_BUILD COMMAND ${CMAKE_COMMAND}
#            -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets
#            DEPENDS ${CMAKE_BINARY_DIR}/bin/assets
#    )
#endif (WIN32)
