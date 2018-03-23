#version 400 core

in vec3 t_normal;
in vec2 t_uv;

out vec4 o_fragment;
out vec2 o_discard;

uniform sampler2D sampler;

void main() {

    vec3 light_position = vec3(0.0, 1.0, 0.0 );
    vec3 light_direction = vec3(0.0, -1.0, 0.0 ); // this is actually position
    vec3 light_colour = vec3(1.0, 1.0, 1.0);
    float brightness = clamp( dot( t_normal, light_direction ), 0.0, 1.0 );
    vec3 diffuse = brightness * light_colour;

    // TODO
    // This stops variable from being optimised out.
    o_discard = t_uv;

    o_fragment = vec4( diffuse, 1.0 + t_uv.x );
}


