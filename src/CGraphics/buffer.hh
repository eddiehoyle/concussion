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

} // namespace graphics

} // namespace concussion

#endif //CONCUSSION_BUFFER_HH
