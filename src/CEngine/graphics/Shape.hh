#ifndef CONCUSSION_SHAPE_HH
#define CONCUSSION_SHAPE_HH

#include <GL/glew.h>

#include <vector>
#include <memory>

namespace concussion {

namespace graphics {

typedef std::vector< GLfloat > Vertices;
typedef std::vector< GLfloat > Normals;
typedef std::vector< GLfloat > Uvs;
typedef std::vector< GLuint > Indices;

struct Shape {
    Vertices vertices;
    Normals normals;
    Uvs uvs;
    Indices indices;
};

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_SHADER_HH
