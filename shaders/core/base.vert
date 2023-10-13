#version 450

// Basic MVP
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 UV;

// These must be set correctly if building another shader used in Model.draw()
layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;
layout(location = 3) uniform mat4 rotation;

out vec3 vNormal;
out vec3 vViewNormal;
out vec3 vPosition;
out vec2 vUV;

void main() {
    vPosition = (model * vec4(position, 1.0)).xyz;
    gl_Position = projection * view * model * vec4(position, 1.0);

    vNormal = (rotation * vec4(normal, 1.0)).xyz;
    vViewNormal = (rotation * view * vec4(normal, 1.0)).xyz;
    vUV = UV;
}