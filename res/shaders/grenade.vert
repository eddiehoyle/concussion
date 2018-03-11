#version 400 core

in vec3 i_position;
in vec3 i_normal;
in vec2 i_uv;

out vec3 t_normal;
out vec2 t_uv;
out vec3 t_color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 toLightVector;


void main( void ) {
    gl_Position = u_projection * u_view * u_model * vec4( i_position, 1.0 );

    // Transient
    t_normal = ( transpose( inverse( u_model ) ) * vec4( i_normal, 0.0 ) ).xyz;
    t_uv = i_uv;
    t_color = vec3( i_position.x + 0.5f, 1.0f, i_position.y + 0.5f );
}