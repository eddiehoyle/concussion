#include <CBase/assert.hh>
#include <cmath>
#include "mesh.hh"

namespace concussion {

namespace graphics {

void circle( float radius,
             unsigned int subdivisions,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLuint >& o_indices ) {
    CNC_ASSERT( subdivisions >= 3 );
    CNC_ASSERT( radius > 0.0f );
    o_vertices.resize( subdivisions * 3 + 3 );
    o_indices.resize( subdivisions * 3 + 3 );
    for ( unsigned int i = 0; i <= subdivisions; ++i ) {
        o_vertices[ 3 * i ] = std::cos( i * ( ( 2.0f * 3.14159f ) / subdivisions ) ) * radius;
        o_vertices[ 3 * i + 1 ] = std::sin( i * ( ( 2.0f * 3.14159f ) / subdivisions ) ) * radius;
        o_vertices[ 3 * i + 2 ] = 0.0f;
        o_indices[ 3 * i ] = 0;
        o_indices[ 3 * i + 1 ] = static_cast< GLuint >( i );
        o_indices[ 3 * i + 2 ] = static_cast< GLuint >( i +1 );
    }
}

void square( float size,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLuint >& o_indices ) {
    CNC_ASSERT( size > 0.0f );

    /// TODO
    /// Tidy this up.
    o_vertices = {
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f
    };

    for ( std::size_t i = 0; i < o_vertices.size(); ++i ) {
        o_vertices[ i ] *= size;
    }

    o_indices = {
            0, 1, 3,
            3, 1, 2
    };
}



} // namespace graphics

} // namespace concussion
