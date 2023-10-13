#version 450

#include "../common/pbr.glsl"
#include "../common/common.glsl"

in vec2 vUV;

uniform sampler2D sampler_base_color;
uniform sampler2D sampler_met_rough_ref;
uniform sampler2D sampler_emissive;
uniform sampler2D sampler_normal;
uniform sampler2D sampler_position;
uniform sampler2D sampler_occ_cc_ccrough;

uniform samplerCube cubemap;

uniform mat4x4 view;
uniform mat4x4 projection;

out vec3 color;

vec3 l = vec3(0.0, -1.0f, 0.0f);

void main() {
    vec4 base_color = texture(sampler_base_color, vUV).rgba;

    if (base_color.a < 0.0001) {
        discard;
    }

    // Geometry values
    vec3 n = texture(sampler_normal, vUV).rgb;
    vec3 position = texture(sampler_position, vUV).rgb;

    // Material values
    float metallic = texture(sampler_met_rough_ref, vUV).r;
    float perceptual_roughness = texture(sampler_met_rough_ref, vUV).g;
    float reflectance = texture(sampler_met_rough_ref, vUV).b;
    float occlusion = texture(sampler_occ_cc_ccrough, vUV).r;
    float clearcoat = texture(sampler_occ_cc_ccrough, vUV).g;
    float clearcoatPerceptualRoughness = texture(sampler_occ_cc_ccrough, vUV).b;
    vec3 emissive = texture(sampler_emissive, vUV).rgb;

    vec3 camera_pos = inverse(view)[3].xyz;

    float a = perceptual_roughness;

    // Too lazy to add another uniform, my uniform management is bad enough as it is
    vec3 v = normalize(position - camera_pos);
    vec3 h = normalize(v + l);
    float NoV = abs(dot(n, v)) + 1e-5;
    float NoL = clamp(dot(n, l), 0.0, 1.0);
    float NoH = clamp(dot(n, h), 0.0, 1.0);
    float LoH = clamp(dot(l, h), 0.0, 1.0);
    vec3 f0 = computeF0(base_color, metallic, reflectance);

    float D = D_GGX(NoH, a);
    vec3  F = F_Schlick(LoH, f0);
    float V = V_SmithGGXCorrelated(NoV, NoL, perceptual_roughness);


    // specular BRDF
    vec3 Fr = (D * V) * F;

    // diffuse BRDF
    vec3 Fd = base_color.xyz * Fd_Lambert();

//    color = D_GGX_fast(perceptual_roughness, NoH, n, h).xxx;
//    color = D_GGX(NoH, perceptual_roughness).xxx;
//    color =   NoH.xxx;
//    color = V_SmithGGXCorrelated(NoV, NoL, perceptual_roughness).xxx;
//    color = v.xxx;
//    color = v;
    // Values taken from the filament source code
//    color = F_Schlick(0.04, 1.0, VoH).xxx;
    color = Fd + Fr;
}


