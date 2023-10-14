#version 450

#include "../common/pbr.glsl"
#include "../common/common.glsl"

in vec2 vUV;

layout(binding = 0) uniform sampler2D sampler_base_color;
layout(binding = 1) uniform sampler2D sampler_met_rough_ref;
layout(binding = 2) uniform sampler2D sampler_emissive;
layout(binding = 3) uniform sampler2D sampler_normal;
layout(binding = 4) uniform sampler2D sampler_position;
layout(binding = 5) uniform sampler2D sampler_occ_cc_ccrough;

layout(binding = 6) uniform samplerCube cubemap;

uniform mat4x4 view;
uniform mat4x4 projection;

out vec3 color;

vec3 lightDirection = vec3(0.0, -1.0f, 0.0f);
float lightIntensity = 3.0f;


//vec3 ibl(vec3 n, vec3 v, vec3 diffuseColor, vec3 f0, vec3 f90, float perceptualRoughness) {
//    vec3 r = reflect(n);
//    vec3 Ld = textureCube(cubemap, r) * diffuseColor;
//    vec3 Lld = textureCube(cubemap, r);
////    vec2 Ldfg = textureLod(dfgLut, vec2(dot(n, v), perceptualRoughness), 0.0).xy;
//    vec2 Ldfg = vec2(0.9, 0.9);
//    vec3 Lr =  (f0 * Ldfg.x + f90 * Ldfg.y) * Lld;
//    return Ld + Lr;
//}


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
    float clearCoatPerceptualRoughness = texture(sampler_occ_cc_ccrough, vUV).b;
    vec3 emissive = texture(sampler_emissive, vUV).rgb;

    // Camera
    // Too lazy to add another uniform, my uniform management is bad enough as it is
    vec3 camera_pos = inverse(view)[3].xyz;

    // Parameter remapping
    float a = perceptual_roughness * perceptual_roughness;
    vec3 diffuseColor = (1.0 - metallic) * base_color.rgb;
    vec3 l = normalize(-lightDirection);

    vec3 v = normalize(position - camera_pos);
    vec3 h = normalize(v + l);
    float NoV = abs(dot(n, v)) + 1e-5;
    float NoL = clamp(dot(n, l), 0.0, 1.0);
    float NoH = clamp(dot(n, h), 0.0, 1.0);
    float LoH = clamp(dot(l, h), 0.0, 1.0);
    vec3 f0 = 0.16 * reflectance * reflectance * (1.0 - metallic) + base_color.rgb * metallic;

    float D = D_GGX(NoH, a);
    vec3  F = F_Schlick(LoH, f0);
    float V = V_SmithGGXCorrelated(NoV, NoL, a);

    // specular BRDF
    vec3 Fr = (D * V) * F;// * texture(cubemap, reflect(v, n)).rgb;

    // diffuse BRDF
    vec3 Fd = diffuseColor * Fd_Lambert();
//    vec3 Fd = diffuseColor * Fd_Burley(NoV, NoL, LoH, a);

    float illuminance = lightIntensity * NoL;
    vec3 luminance = illuminance * (Fr + Fd);

    //    color = D_GGX_fast(perceptual_roughness, NoH, n, h).xxx;
    //    color = D_GGX(NoH, perceptual_roughness).xxx;
    //    color =   NoH.xxx;
    //    color = V_SmithGGXCorrelated(NoV, NoL, perceptual_roughness).xxx;
    //    color = v.xxx;
    //    color = v;
    // Values taken from the filament source code
    //    color = F_Schlick(0.04, 1.0, VoH).xxx;
//        color = Fd + Fr;
    color = luminance;
//    color = texture(cubemap, reflect(v, n)).rgb;
}