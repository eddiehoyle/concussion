#include "buffer.hh"

namespace concussion {

namespace graphics {

GLuint create_vao() {
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    return vao;
}

void bind_vao( GLuint vao ) {
    glBindVertexArray( vao );
}

void buffer_indices( const std::vector< GLuint >& indices ) {
    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * indices.size(), &indices[0], GL_STATIC_DRAW );
}

void buffer_data( GLuint index, GLsizei coordinates, GLenum type, const std::vector< GLfloat >& data ) {
    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * data.size(), &data[0], GL_STATIC_DRAW );
    glVertexAttribPointer( index, coordinates, type, GL_FALSE, 0, 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void unbind_vao() {
    glBindVertexArray( 0 );
}

} // namespace graphics

} // namespace concussion
