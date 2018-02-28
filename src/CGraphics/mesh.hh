#ifndef CONCUSSION_MESH_HH
#define CONCUSSION_MESH_HH

#include <GL/glew.h>

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace concussion {

namespace graphics {

GLuint buffer( GLfloat vertices[], GLsizei vertex_count, GLuint indices[], GLsizei index_count );

struct Mesh {
    GLuint vao;
};

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_SHADER_HH
