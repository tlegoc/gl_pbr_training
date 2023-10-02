#version 450

layout(location = 0) out vec4 base_color;
layout(location = 1) out vec3 met_rough_ref;
layout(location = 2) out vec3 emissive;
layout(location = 3) out vec3 normal;
layout(location = 4) out vec3 position;
layout(location = 5) out vec3 occ_cc_ccrough;

in vec3 vNormal;
in vec3 vViewNormal;
in vec2 vUV;
in vec3 vPosition;

uniform vec4 ubase_color = vec4(0.81, 0.0, 0.0, 1.0);
uniform float umetallic = 0.0f;
uniform float uroughness = 1.0f;
uniform float ureflectance = 0.5f;
uniform vec3 uemissive = vec3(0.0, 0.0, 0.0);

void main() {
    base_color = ubase_color;

    met_rough_ref = vec3(umetallic, uroughness, ureflectance);

    emissive = uemissive;
    normal = vNormal;
    position = vPosition;

    occ_cc_ccrough = vec3(0.0, 0.0, 0.0);
}
