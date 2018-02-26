#ifndef CONCUSSION_MANAGER_HH
#define CONCUSSION_MANAGER_HH

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

private:
    ShaderManager() = default;
    static ShaderManager* s_instance;
};

} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_MANAGER_HH
