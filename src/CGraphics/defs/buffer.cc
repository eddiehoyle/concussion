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

// ------------------------------------------------------------------------------------------------------ //

ElementArrayBuffer::ElementArrayBuffer( GLsizei size, GLenum usage ) {
    glGenBuffers( 1, &m_id );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_id );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_size, nullptr, m_usage );
}

ElementArrayBuffer::~ElementArrayBuffer() {
    glDeleteBuffers( 1, &m_id );
}

void ElementArrayBuffer::send( GLvoid* data, GLsizeiptrARB size, GLintptrARB offset ) {
    glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, offset, size, data );
}

// ------------------------------------------------------------------------------------------------------ //

AttributeArrayBuffer::AttributeArrayBuffer( GLsizei coordinates,
                                            GLsizei size,
                                            GLenum type,
                                            GLenum normalized,
                                            GLenum usage ) {
    glGenBuffers( 1, &m_id );
    glBindBuffer( GL_ARRAY_BUFFER, m_id );
    glBufferData( GL_ARRAY_BUFFER, m_size, nullptr, m_usage );
}

AttributeArrayBuffer::~AttributeArrayBuffer() {
    glDeleteBuffers( 1, &m_id );
}

GLenum AttributeArrayBuffer::get_type() const {
    return m_type;
}

bool AttributeArrayBuffer::is_normalized() const {
    return m_normalized;
}

GLsizei AttributeArrayBuffer::get_coordinates() const {
    return m_coordinates;
}

void AttributeArrayBuffer::send( GLvoid* data, GLsizeiptrARB size, GLintptrARB offset ) {
    glBufferSubData( GL_ARRAY_BUFFER, offset, size, data );
}

void AttributeArrayBuffer::bind() {
    glBindBuffer( GL_ARRAY_BUFFER, m_id );
}

void AttributeArrayBuffer::unbind() {
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}



} // namespace graphics

} // namespace concussion
