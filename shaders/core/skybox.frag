#version 450

in vec3 vUV;

uniform samplerCube cubemap;

out vec3 color;

void main() {
    color = texture(cubemap, vUV).rgb;
}
