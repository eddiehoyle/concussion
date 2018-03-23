

#include <CBase/resource.hh>
#include <CBase/assert.hh>
#include <CGraphics/shape.hh>
#include <CBase/model.hh>
#include "geometry/cube.hh"
#include "buffer.hh"

namespace concussion {

namespace graphics {


void drawCube( GLuint indices_count ) {
    glDrawElements( GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0 );
}

Cube::Cube()
        : Mesh() {

    bool result;
    const std::string sphere_path = io::find_resource( "cube.obj", result );
    CNC_ASSERT( result );

    graphics::Shape shape;
    load_obj( sphere_path, shape );

    m_count = shape.indices.size();

    bind();

    ElementArrayBuffer* indices_buffer = new ElementArrayBuffer( sizeof( GLuint ) * shape.indices.size(), GL_STATIC_DRAW );
    indices_buffer->send( &shape.indices[0], sizeof( GLuint ) * shape.indices.size(), 0 );
    AttributeArrayBuffer* vertices_buffer = new AttributeArrayBuffer( 3, sizeof( GLfloat ) * shape.vertices.size(), GL_FLOAT, GL_FALSE, GL_STATIC_DRAW );
    vertices_buffer->send( &shape.vertices[0], sizeof( GLfloat ) * shape.vertices.size(), 0 );
    AttributeArrayBuffer* normals_buffer = new AttributeArrayBuffer( 3, sizeof( GLfloat ) * shape.normals.size(), GL_FLOAT, GL_FALSE, GL_STATIC_DRAW );
    normals_buffer->send( &shape.normals[0], sizeof( GLfloat ) * shape.normals.size(), 0 );
    AttributeArrayBuffer* uvs_buffer = new AttributeArrayBuffer( 2, sizeof( GLfloat ) * shape.uvs.size(), GL_FLOAT, GL_FALSE, GL_STATIC_DRAW );
    uvs_buffer->send( &shape.uvs[0], sizeof( GLfloat ) * shape.uvs.size(), 0 );

    attach( indices_buffer );
    attach( 0, vertices_buffer );
    attach( 1, normals_buffer );
    attach( 2, uvs_buffer );

    unbind();

    setDrawFunc( drawCube );
}

} // namespace graphics

} // namespace concussion