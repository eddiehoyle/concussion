#include "graphics/ShaderManager.hh"
#include "Render.hh"

namespace concussion {

namespace graphics {

void StaticRender::buffer( const MeshPtr& mesh ) {
    m_meshes.push_back( mesh );
}

void StaticRender::bind( const MeshPtr& mesh ) {
    glBindVertexArray( mesh->get_vao() );
}

void StaticRender::unbind() {
    glBindVertexArray( 0 );
}

void StaticRender::enable( const MeshPtr& mesh ) {
    for ( const auto& attribute : mesh->get_attributes() ) {
        glEnableVertexAttribArray( attribute );
    }
}

void StaticRender::disable( const MeshPtr& mesh ) {
    for ( const auto& attribute : mesh->get_attributes() ) {
        glDisableVertexAttribArray( attribute );
    }
}

void StaticRender::draw() {
    for ( const auto& mesh : m_meshes ) {

        bind( mesh );
        enable( mesh );

        glDrawElements( GL_TRIANGLES, mesh->get_indices_count(), GL_UNSIGNED_INT, 0 );

        disable( mesh );
        unbind();
    }
    m_meshes.clear();
}

} // namespace graphics

} // namespace concussion

