#version 450

layout(location = 0) out vec3 base_color;
layout(location = 1) out float metallic;
layout(location = 2) out float roughness;
layout(location = 3) out float reflectance;
layout(location = 4) out vec3 emissive;
layout(location = 5) out vec3 normal;
layout(location = 6) out float occlusion;

in vec3 vNormal;
in vec2 vUV;

void main() {
    base_color = vec3(0.0, 1.0, 0.0);
    metallic = 0.0;
    roughness = 0.5;
    reflectance = 0.5;
    emissive = vec3(0.0, 0.0, 0.0);
    normal = vNormal;
    occlusion = 1.0;
}
