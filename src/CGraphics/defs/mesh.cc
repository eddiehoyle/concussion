#include <CBase/assert.hh>
#include "mesh.hh"

namespace concussion {

namespace graphics {

void buffer_vertices( GLfloat data[], GLsizei size ) {
    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( &data[0] ) * size, &data[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void buffer_indices( GLuint data[], GLsizei size ) {
    GLuint ebo;
    glGenBuffers( 1, &ebo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( &data[0] ) * size, &data[0], GL_STATIC_DRAW );
}

GLuint buffer( GLfloat vertices[], GLsizei vertex_count, GLuint indices[], GLsizei index_count ) {

    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    buffer_vertices( vertices, vertex_count );
    buffer_indices( indices, index_count );

    glBindVertexArray( 0 );

    return vao;
}

} // namespace graphics

} // namespace concussion
