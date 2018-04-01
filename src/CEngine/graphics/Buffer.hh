#ifndef CONCUSSION_BUFFER_HH
#define CONCUSSION_BUFFER_HH

#include <GL/glew.h>

#include <vector>

namespace concussion {

namespace graphics {

GLuint create_vao();
void bind_vao( GLuint vao );
void buffer_indices( const std::vector< GLuint >& indices );
void buffer_data( GLuint index,
                  GLsizei coordinates,
                  const std::vector< GLfloat >& data );
void unbind_vao();

// ------------------------------------------------------------------------------------------------------ //

class ElementArrayBuffer {
public:
    ElementArrayBuffer( GLsizei size, GLenum usage );
    ~ElementArrayBuffer ();
    void send( GLvoid* data, GLsizeiptrARB size, GLintptrARB offset );
private:
    GLuint m_id;
    GLsizei m_size;
    GLenum m_usage;
};

// ------------------------------------------------------------------------------------------------------ //

class AttributeArrayBuffer {
public:
    AttributeArrayBuffer( GLsizei coordinates, GLsizei size, GLenum type, GLenum normalized, GLenum usage );
    ~AttributeArrayBuffer();
    void send( GLvoid* data, GLsizeiptrARB size, GLintptrARB offset );
    GLsizei get_coordinates() const;
    GLenum get_type() const;
    bool is_normalized() const;

    void bind();
    void unbind();

private:
    GLuint m_id;
    GLsizei m_coordinates;
    GLsizei m_size;
    GLenum m_type;
    GLenum m_normalized;
    GLenum m_usage;
};

// ------------------------------------------------------------------------------------------------------ //


// ------------------------------------------------------------------------------------------------------ //

} // namespace graphics

} // namespace concussion

#endif //CONCUSSION_BUFFER_HH
