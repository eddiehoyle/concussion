#include "manager.hh"

namespace concussion {

namespace graphics {

ShaderManager* ShaderManager::s_instance = nullptr;

ShaderManager* ShaderManager::instance() {
    if ( s_instance == nullptr ) {
        s_instance = new ShaderManager();
    }
    return s_instance;
}

ShaderManager::~ShaderManager() {
    delete s_instance;
}




} // namespace graphics

} // namespace concussion