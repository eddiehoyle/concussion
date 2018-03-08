#version 400 core

in vec2 t_uv;
in vec3 t_color;

out vec4 o_fragment;

const float density = 0.08f;

uniform sampler2D sampler;

void main() {
    if(fract(t_uv.x / density) < 0.1f || fract(t_uv.y / density) < 0.1f)
        o_fragment = vec4( 1.0, 1.0, 1.0, 0.2 );
    else
        discard;
}


