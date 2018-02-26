#include "domain.hh"

namespace concussion {

namespace graphics {

template< typename ShaderT >
ShaderDomain< ShaderT >::ShaderDomain( ShaderT shader )
        : m_shader( shader ) {
}

template< typename ShaderT >
void ShaderDomain< ShaderT >::bind() {
    glUseProgram( m_shader->program() );
}


} // namespace graphics

} // namespace concussion
