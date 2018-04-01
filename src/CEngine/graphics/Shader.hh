#ifndef CONCUSSION_SHADER_HH
#define CONCUSSION_SHADER_HH

#include <GL/glew.h>

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace concussion {

namespace graphics {

class ShaderSource;
class ShaderTarget;

typedef std::map< const char*, GLuint > AttributeMap;
typedef std::map< const char*, GLuint > UniformMap;
typedef std::vector< const char* > Attributes;
typedef std::vector< const char* > Uniforms;
typedef std::shared_ptr< ShaderTarget > ShaderTargetPtr;

struct ShaderSource {
    const char* name;
    const char* vertex;
    const char* fragment;
    Attributes attributes;
    Uniforms uniforms;
};

struct ShaderTarget {
    const char* name;
    GLuint program;
    GLuint vertex;
    GLuint fragment;
    AttributeMap attributes;
    UniformMap uniforms;
};

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_SHADER_HH
