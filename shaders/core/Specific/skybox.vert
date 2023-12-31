#version 430

layout(location = 0) in vec3 position;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

out vec3 vUV;

void main() {
    vUV = position;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
