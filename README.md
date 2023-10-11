# gl_pbr_training

Small OpenGL experiment meant to understand deferred rendering and PBR.
The overall "rendergraph"/rendering engine could be improved to be more flexible and less hardcoded.
Code is also very bad on some parts (shader/material, shader parameters, how textures and framebuffers are handled).

# How to build

Use vcpkg+cmake, compiled successfuly with VS2022 CL on windows and GCC on linux.
