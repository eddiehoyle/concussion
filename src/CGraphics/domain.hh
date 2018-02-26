#ifndef CONCUSSION_DOMAIN_HH
#define CONCUSSION_DOMAIN_HH

#include "shader.hh"

namespace concussion {

namespace graphics {

typedef std::shared_ptr< SimpleShader > SimpleShaderPtr;

template< typename ShaderT >
class ShaderDomain {
public:
    ShaderDomain( ShaderT shader );
    ~ShaderDomain() = default;

    void bind();

private:
    ShaderT m_shader;

};

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_DOMAIN_HH
