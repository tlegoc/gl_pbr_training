#version 450
// Implementation heavily based on Google's filament
// https://google.github.io/filament/Filament.html

in vec2 vUV;

uniform sampler2D sampler_base_color;
uniform sampler2D sampler_met_rough_ref;
uniform sampler2D sampler_emissive;
uniform sampler2D sampler_normal;
uniform sampler2D sampler_occ_cc_ccrough;

uniform samplerCube cubemap;

out vec3 color;

#define PI 3.141592653589793238462643383279

#define IGNORE_TRESHOLD 0.001

float D_GGX(float NoH, float a) {
    float a2 = a * a;
    float f = (NoH * a2 - NoH) * NoH + 1.0;
    return a2 / (PI * f * f);
}

vec3 F_Schlick(float u, vec3 f0) {
    return f0 + (vec3(1.0) - f0) * pow(1.0 - u, 5.0);
}

float V_SmithGGXCorrelated(float NoV, float NoL, float a) {
    float a2 = a * a;
    float GGXL = NoV * sqrt((-NoL * a2 + NoL) * NoL + a2);
    float GGXV = NoL * sqrt((-NoV * a2 + NoV) * NoV + a2);
    return 0.5 / (GGXV + GGXL);
}

float Fd_Lambert() {
    return 1.0 / PI;
}

float V_Kelemen(float LoH) {
    return 0.25 / (LoH * LoH);
}

struct MaterialProperties {
    float perceptualRoughness;
    float reflectance;
    float metallic;
    vec3 baseColor;
};

vec3 BRDF(vec3 v, vec3 l, vec3 n, MaterialProperties mp) {
    l *= vec3(0.0, -1.0, 0.0);
    vec3 diffuseColor = (1.0 - mp.metallic) * mp.baseColor;

    vec3 f0 = 0.16 * mp.reflectance * mp.reflectance * (1.0 - mp.metallic) + mp.baseColor * mp.metallic;

    vec3 h = normalize(v + l);

    float NoV = abs(dot(n, v)) + 1e-5;
    float NoL = clamp(dot(n, l), 0.0, 1.0);
    float NoH = clamp(dot(n, h), 0.0, 1.0);
    float LoH = clamp(dot(l, h), 0.0, 1.0);

    // perceptually linear roughness to roughness (see parameterization)
    float roughness = mp.perceptualRoughness * mp.perceptualRoughness;

    float D = D_GGX(NoH, roughness);
    vec3  F = F_Schlick(LoH, f0);
    float V = V_SmithGGXCorrelated(NoV, NoL, roughness);

    // specular BRDF
    vec3 Fr = (D * V) * F;

    // diffuse BRDF
    vec3 Fd = diffuseColor * Fd_Lambert();

    // vec3 energyCompensation = 1.0 + mp.f0 * (1.0 / dfg.y - 1.0);
    // Scale the specular lobe to account for multiscattering
    // Fr *= pixel.energyCompensation;

    return Fd + Fr;
}

void main() {
    vec4 base_color = texture(sampler_base_color, vUV).rgba;

    if (base_color.a < IGNORE_TRESHOLD) {
        discard;
    }

    float metallic = texture(sampler_met_rough_ref, vUV).r;
    float perceptual_roughness = texture(sampler_met_rough_ref, vUV).g;
    float reflectance = texture(sampler_met_rough_ref, vUV).b;

    vec3 emissive = texture(sampler_emissive, vUV).rgb;
    vec3 normal = texture(sampler_normal, vUV).rgb;

    float occlusion = texture(sampler_occ_cc_ccrough, vUV).r;
    float clearcoat = texture(sampler_occ_cc_ccrough, vUV).g;
    float clearcoatPerceptualRoughness = texture(sampler_occ_cc_ccrough, vUV).b;

    MaterialProperties mp;
    mp.perceptualRoughness = perceptual_roughness;
    mp.reflectance = reflectance;
    mp.metallic = metallic;
    mp.baseColor = base_color.rgb;

//    color = BRDF(normalize(vec3(0.0, -1.0, -1.0)), vec3(0.0, -1.0, 0.0), normal, mp);
    color = texture(cubemap, normal).rgb;
}
