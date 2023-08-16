#version 450

// Basic MVP

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 UV;

// These must be set correctly
layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

out vec3 vNormal;
out vec2 vUV;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);

    // vec3 world_space_normal = vec3(model_matrix * vec4(vertex_normal, 0.0));
    // vec3 view_space_normal = vec3(view_matrix * model_matrix * vec4(vertex_normal, 0.0));
    vNormal = vec3(model * vec4(normal, 0.0));
    vUV = UV;
}