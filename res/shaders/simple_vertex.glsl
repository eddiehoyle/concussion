#version 400

in vec3 i_position;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main( void ) {
    gl_Position = vec4( 0.0, 0.0, 0.0, 0.0 );
}