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

void buffer_data( GLuint index, GLsizei coordinates, const std::vector< GLfloat >& data ) {
    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * data.size(), &data[0], GL_STATIC_DRAW );
    glVertexAttribPointer( index, coordinates, GL_FLOAT, GL_FALSE, 0, 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void unbind_vao() {
    glBindVertexArray( 0 );
}

BufferObject::BufferObject( GLenum target, GLsizei size, GLenum usage )
        : m_id( 0 ),
          m_target( target ),
          m_size( size ),
          m_usage( usage ),
          m_allocated( false ) {
    glGenBuffers( 1, &m_id );
    glBindBuffer(m_target, m_id);
    glBufferData(m_target, m_size, nullptr, m_usage);
    m_allocated = true;
}

BufferObject::~BufferObject() {
    glDeleteBuffers(1, &m_id);
    m_allocated = false;
}

GLuint BufferObject::id() const {
    return m_id;
}

void BufferObject::send( GLvoid* data ) {
    glBufferSubData( m_target, 0, m_size, data );
}

void BufferObject::bind() {
    glBindBuffer(m_target, m_id);
}

void BufferObject::unbind() {
    GLenum targets = GL_ARRAY_BUFFER | GL_ELEMENT_ARRAY_BUFFER;
    glBindBuffer( targets, 0 );
}

} // namespace graphics

} // namespace concussion
