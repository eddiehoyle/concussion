#ifndef CONCUSSION_SHADER_HH
#define CONCUSSION_SHADER_HH

#include <GL/glew.h>

#include <string>
#include <map>

namespace concussion {

namespace graphics {


typedef std::map< const char*, GLuint > UniformMap;

class SimpleShader {
public:
    SimpleShader();
    ~SimpleShader();

    SimpleShader( SimpleShader& ) = delete;
    SimpleShader& operator=( const SimpleShader& ) = delete;
    SimpleShader& operator=( SimpleShader&& ) = delete;

    GLuint program() const;
    void find_uniform( const char* name, GLuint* uniform );

private:
    void initialise_uniform( const char *name, GLuint *uniform );

private:
    GLuint m_program;
    GLuint m_vertex;
    GLuint m_fragment;

    UniformMap m_uniforms;
};

} // namespace graphics

} // namespace concussion

#endif //CONCUSSION_SHADER_HH
