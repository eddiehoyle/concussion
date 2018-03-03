#include "shape.hh"

namespace concussion {

namespace graphics {

Shape::Shape( GLuint vao )
        : m_vao( vao ) {
}

void Shape::bind() {
    glBindVertexArray( m_vao );

    /// TODO
    /// Bind attributes here? Or elsewhere?

}

void Shape::unbind() {
    glBindVertexArray( 0 );
}

} // namespace graphics

} // namespace concussion
