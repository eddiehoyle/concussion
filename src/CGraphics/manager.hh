#ifndef CONCUSSION_MANAGER_HH
#define CONCUSSION_MANAGER_HH

#include "shader.hh"

#include <GL/glew.h>

#include <map>
#include <vector>

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

    void add( const ShaderSource& source );
    void bind( const char* name );
    void unbind();


private:
    ShaderManager() = default;
    static ShaderManager* s_instance;

    std::map< const char*, ShaderTargetPtr > m_shaders;
};

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_MANAGER_HH
