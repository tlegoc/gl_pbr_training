# gl_pbr_training

Small OpenGL experiment meant to understand deferred rendering and PBR.
The overall "rendergraph"/rendering engine could be improved to be more flexible and less hardcoded.
Code is also very bad on some parts (shader/material, shader parameters, how textures and framebuffers are handled).

# How to build

Enable symlinks if you're on windows.
Use vcpkg+cmake, compiled successfuly with VS2022 CL on windows and GCC on linux.

![image](https://github.com/tlegoc/gl_pbr_training/assets/21106616/de81b769-1d4e-401a-835b-5f3fa944a242)
