#ifndef CONCUSSION_MANAGER_HH
#define CONCUSSION_MANAGER_HH

#include "Shader.hh"

#include <GL/glew.h>

#include <map>
#include <vector>
#include <glm/detail/type_mat.hpp>

namespace concussion {

namespace graphics {

class ShaderManager {

public:
    static ShaderManager* instance();

public:
    ShaderManager( const ShaderManager& ) = delete;
    ShaderManager& operator=( const ShaderManager& ) = delete;
    ShaderManager& operator=( ShaderManager&& ) = delete;
    ~ShaderManager();

    void compile( const ShaderSource& source );
    void bind( const char* name );
    void unbind();

    void load( const char* uniform, const glm::mat4& matrix );
    void load( const char* uniform, float value );

private:
    ShaderManager() = default;
    static ShaderManager* s_instance;

    std::map< const char*, ShaderTargetPtr > m_shaders;

    ShaderTargetPtr m_active;
};

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_MANAGER_HH
