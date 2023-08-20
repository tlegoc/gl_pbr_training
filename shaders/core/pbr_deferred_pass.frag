#version 450
// Implementation heavily based on Google's filament
// https://google.github.io/filament/Filament.html

#include "pbr.glsl"

in vec2 vUV;

uniform sampler2D sampler_base_color;
uniform sampler2D sampler_met_rough_ref;
uniform sampler2D sampler_emissive;
uniform sampler2D sampler_normal;
uniform sampler2D sampler_position;
uniform sampler2D sampler_occ_cc_ccrough;

uniform samplerCube cubemap;

out vec3 color;

struct CameraProperties {
    vec3 position;
};


void main() {
    vec4 base_color = texture(sampler_base_color, vUV).rgba;

    if (base_color.a < IGNORE_TRESHOLD) {
        discard;
    }

    // Geometry values
    vec3 normal = texture(sampler_normal, vUV).rgb;
    vec3 position = texture(sampler_position, vUV).rgb;

    // Material values
    float metallic = texture(sampler_met_rough_ref, vUV).r;
    float perceptual_roughness = texture(sampler_met_rough_ref, vUV).g;
    float reflectance = texture(sampler_met_rough_ref, vUV).b;
    float occlusion = texture(sampler_occ_cc_ccrough, vUV).r;
    float clearcoat = texture(sampler_occ_cc_ccrough, vUV).g;
    float clearcoatPerceptualRoughness = texture(sampler_occ_cc_ccrough, vUV).b;
    vec3 emissive = texture(sampler_emissive, vUV).rgb;

    MaterialProperties mp;
    mp.perceptual_roughness = perceptual_roughness;
    mp.reflectance = reflectance;
    mp.metallic = metallic;
    mp.base_color = base_color.rgb;

//    color = BRDF(normalize(vec3(0.0, -1.0, -1.0)), vec3(0.0, -1.0, 0.0), normal, mp);
//    color = texture(cubemap, reflect(normal, normal)).rgb;
    color = position;
}

