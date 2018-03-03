#ifndef CONCUSSION_SHAPE_HH
#define CONCUSSION_SHAPE_HH

#include <GL/glew.h>
#include <memory>

namespace concussion {

namespace graphics {

class Shape {

public:
    explicit Shape( GLuint vao );
    void bind();
    void unbind();

private:
    GLuint m_vao;
};

typedef std::shared_ptr< Shape > ShapePtr;

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_SHADER_HH
