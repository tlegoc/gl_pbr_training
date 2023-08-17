#version 450
// Implementation based on Google's filament
// https://google.github.io/filament/Filament.html

in vec2 vUV;

uniform sampler2D sampler_base_color;
uniform sampler2D sampler_metallic;
uniform sampler2D sampler_roughness;
uniform sampler2D sampler_reflectance;
uniform sampler2D sampler_emissive;
uniform sampler2D sampler_normal;
uniform sampler2D sampler_occlusion;

out vec3 color;

void main() {
    vec3 base_color = texture(sampler_base_color, vUV).rgb;
    vec3 emissive = texture(sampler_emissive, vUV).rgb;
    float metallic = texture(sampler_metallic, vUV).r;
    float roughness = texture(sampler_roughness, vUV).r;
    float reflectance = texture(sampler_reflectance, vUV).r;
    float occlusion = texture(sampler_occlusion, vUV).r;
    vec3 normal = texture(sampler_normal, vUV).rgb;

    color = base_color;
}
