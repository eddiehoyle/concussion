#ifndef CONCUSSION_SHADER_HH
#define CONCUSSION_SHADER_HH

#include <GL/glew.h>

#include <string>
#include <vector>
#include <map>

namespace concussion {

namespace graphics {

class ShaderSource;
class ShaderTarget;

typedef std::map< const char*, GLuint > AttributeMap;
typedef std::map< const char*, GLuint > UniformMap;
typedef std::vector< const char* > Attributes;
typedef std::vector< const char* > Uniforms;
typedef std::unique_ptr< ShaderTarget > ShaderTargetPtr;

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



//
//
//
////typedef std::map< const char*, GLuint > UniformMap;
//
//class SimpleShader {
//public:
//    SimpleShader();
//    ~SimpleShader();
//
//    SimpleShader( SimpleShader& ) = delete;
//    SimpleShader& operator=( const SimpleShader& ) = delete;
//    SimpleShader& operator=( SimpleShader&& ) = delete;
//
//    GLuint program() const;
//    void find_uniform( const char* name, GLuint* uniform );
//
//private:
//    void initialise_uniform( const char *name, GLuint *uniform );
//
//private:
//    GLuint m_program;
//    GLuint m_vertex;
//    GLuint m_fragment;
//
//    UniformMap m_uniforms;
//};

} // namespace graphics

} // namespace concussion

#endif //CONCUSSION_SHADER_HH
