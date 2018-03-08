#version 400 core

in vec3 i_position;
in vec2 i_uv;

out vec2 t_uv;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main( void ) {
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4( i_position, 1.0 );
    t_uv = i_uv;
}