# IMPORTANT

This project is not finished, and the code quality isn't great. The project is dead, but the core idea still exists and I'll come back to it when I have the time. If you want a better representation of my skills, check out my most recent projects.

# gl_pbr_training

Small OpenGL experiment meant to understand deferred rendering and PBR.
The overall "rendergraph"/rendering engine could be improved to be more flexible and less hardcoded.
Code is also very bad on some parts (shader/material, shader parameters, how textures and framebuffers are handled).

# TODO

- [ ] Improve code quality
- [ ] Better material system
- [ ] True rendergraph implementation
- [ ] Finished basic PBR implementation
- [ ] Scene handling
- [ ] Engine init function

# How to build

Enable symlinks if you're on windows.
Use vcpkg+cmake, compiled successfuly with VS2022 CL on windows and GCC on linux.

![image](https://github.com/tlegoc/gl_pbr_training/assets/21106616/de81b769-1d4e-401a-835b-5f3fa944a242)
