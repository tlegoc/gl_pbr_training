#version 450
// Implementation based on Google's filament
// https://google.github.io/filament/Filament.html

in vec2 UV;

uniform sampler2D sampler_base_color;
uniform sampler2D sampler_metallic;
uniform sampler2D sampler_roughness;
uniform sampler2D sampler_reflectance;
uniform sampler2D sampler_emissive;
uniform sampler2D sampler_normal;
uniform sampler2D sampler_occlusion;

out vec3 color;

void main() {
    vec3 base_color = texture(sampler_base_color, UV);
    vec3 emissive = texture(sampler_emissive, UV).rgb;
    float metallic = texture(sampler_metallic, UV).r;
    float roughness = texture(sampler_roughness, UV).r;
    float reflectance = texture(sampler_reflectance, UV).r;
    float occlusion = texture(sampler_occlusion, UV).r;
    vec3 normal = texture(sampler_normal, UV).rgb;

    color = base_color;
}
