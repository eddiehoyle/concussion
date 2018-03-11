#version 400 core

in vec3 t_normal;
in vec2 t_uv;
in vec3 t_color;

out vec4 o_fragment;

uniform sampler2D sampler;

void main() {

    vec3 light = vec3( 0, -1, 0 );
//    float brightness = max( dot( normalize( t_normal ), light), 0.0 );
//    o_fragment = vec4( t_color * brightness, 1.0 );

    vec3 unitNormal = normalize( t_normal );
    vec3 unitDirection = normalize( light );
    float brightness = max( dot( unitNormal, unitDirection ), 0.0 );
    vec3 diffuse = brightness * vec3(1,1,1);

    o_fragment = vec4( diffuse, 1.0 );// * texture( textureSampler, pass_textureCoords );
}


