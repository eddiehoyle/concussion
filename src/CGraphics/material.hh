#ifndef CONCUSSION_MATERIAL_HH
#define CONCUSSION_MATERIAL_HH

#include <GL/glew.h>

#include <vector>
#include <memory>

namespace concussion {

namespace graphics {

class Shader;

class Material {

private:
    Shader* m_shader;
};

} // namespace graphics

} // namespace concussion

#endif //CONCUSSION_MATERIAL_HH
