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

    // Too lazy to add another uniform, my uniform management is bad enough as it is
    float fov = 2.0*atan( 1.0/projection[1][1] ) * 180.0 / PI;
    vec3 v = (inverse(projection * view) * vec4((vUV - .5f) * fov, 1.0, 1.0)).xyz;
    v = normalize(v);

    vec3 h = normalize(l+v)/2.0f;

    color = D_GGX(dot(h, normal), perceptual_roughness).xxx;
}

