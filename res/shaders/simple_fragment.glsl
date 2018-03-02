#version 400 core

in vec2 t_uv;
in vec3 t_color;

out vec4 o_fragment;

uniform sampler2D sampler;

void main() {
    vec2 temp = t_uv;
    o_fragment = vec4( t_color, 1.0 );
}


