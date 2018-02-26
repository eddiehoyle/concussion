#version 400 core

in vec3 i_position;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main( void ) {
    gl_Position = u_modelMatrix * u_viewMatrix * u_projectionMatrix * vec4( i_position, 1.0 );
}