#ifndef CONCUSSION_RENDER_HH
#define CONCUSSION_RENDER_HH

#include <GL/glew.h>
#include <vector>

#include "CGraphics/geometry/mesh.hh"

namespace concussion {

namespace graphics {

class StaticRender {

public:
    StaticRender() = default;
    ~StaticRender() = default;

    void buffer( const MeshPtr& mesh );
    void draw();

private:
    void bind( const MeshPtr& mesh );
    void unbind();
    void enable( const MeshPtr& mesh );
    void disable( const MeshPtr& mesh );

    std::vector< MeshPtr > m_meshes;
};

} // namespace graphics

} // namespace concussion

#endif //CONCUSSION_RENDER_HH
