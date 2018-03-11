#ifndef CONCUSSION_SHAPE_HH
#define CONCUSSION_SHAPE_HH

#include <GL/glew.h>

#include <vector>
#include <memory>

namespace concussion {

namespace graphics {

struct Shape {
    std::vector< GLuint > indices;
    std::vector< GLfloat > vertices;
    std::vector< GLfloat > uvs;
};

typedef std::shared_ptr< Shape > ShapePtr;

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_SHADER_HH
