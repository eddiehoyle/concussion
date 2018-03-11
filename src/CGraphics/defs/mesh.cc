#include <CBase/assert.hh>
#include <cmath>
#include <tiny_obj_loader.h>
#include <CBase/resource.hh>
#include <CBase/io.hh>
#include "mesh.hh"

namespace concussion {

namespace graphics {

void cube( float size,
           std::vector< GLfloat >& o_vertices,
           std::vector< GLfloat >& o_normals,
           std::vector< GLfloat >& o_uvs,
           std::vector< GLuint >& o_indices ) {

    o_vertices = {
            -1.0f,1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f,1.0f,-1.0f,

            -1.0f,1.0f,1.0f,
            -1.0f,-1.0f,1.0f,
            1.0f,-1.0f,1.0f,
            1.0f,1.0f,1.0f,

            1.0f,1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,1.0f,
            1.0f,1.0f,1.0f,

            -1.0f,1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,1.0f,
            -1.0f,1.0f,1.0f,

            -1.0f,1.0f,1.0f,
            -1.0f,1.0f,-1.0f,
            1.0f,1.0f,-1.0f,
            1.0f,1.0f,1.0f,

            -1.0f,-1.0f,1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,1.0f
    };

    // This is bad. Fix this.
    o_normals = o_vertices;

    o_uvs = {
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0
    };

    o_indices = {
            0,1,3,
            3,1,2,
            4,5,7,
            7,5,6,
            8,9,11,
            11,9,10,
            12,13,15,
            15,13,14,
            16,17,19,
            19,17,18,
            20,21,23,
            23,21,22
    };
}

void circle( float radius,
             unsigned int subdivisions,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLuint >& o_indices,
             std::vector< GLfloat >& o_uvs ) {
    CNC_ASSERT( subdivisions >= 3 );
    CNC_ASSERT( radius > 0.0f );
    o_vertices.resize( subdivisions * 3 + 3 );
    o_indices.resize( subdivisions * 3 + 3 );
    o_uvs.resize( subdivisions * 2 + 2 );
    for ( unsigned int i = 0; i <= subdivisions; ++i ) {
        o_vertices[ 3 * i ] = std::cos( i * ( ( 2.0f * 3.14159f ) / subdivisions ) ) * radius;
        o_vertices[ 3 * i + 1 ] = std::sin( i * ( ( 2.0f * 3.14159f ) / subdivisions ) ) * radius;
        o_vertices[ 3 * i + 2 ] = 0.0f;
        o_indices[ 3 * i ] = 0;
        o_indices[ 3 * i + 1 ] = static_cast< GLuint >( i );
        o_indices[ 3 * i + 2 ] = static_cast< GLuint >( i +1 );
        o_uvs[ 2 * i ] = 0.0f;
        o_uvs[ 2 * i + 1 ] = 0.0f;
    }
}

void square( float size,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLuint >& o_indices,
             std::vector< GLfloat >& o_uvs ) {
    CNC_ASSERT( size > 0.0f );

    /// TODO
    /// Tidy this up.
    o_vertices = {
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
    };

    for ( std::size_t i = 0; i < o_vertices.size(); ++i ) {
        o_vertices[ i ] *= size;
    }

    o_indices = {
            0, 1, 2,
            2, 1, 3
    };

    o_uvs = {
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
    };
}

void sphere( float radius,
             unsigned int rings,
             unsigned int sectors,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLfloat >& o_normals,
             std::vector< GLfloat >& o_uvs,
             std::vector< GLuint >& o_indices ) {

    CNC_ASSERT( rings >= 3 );
    CNC_ASSERT( sectors >= 3 );
    CNC_ASSERT( radius > 0.0f );

    float const R = 1. / ( float )( rings - 1 );
    float const S = 1. / ( float )( sectors - 1 );
    int r, s;

    o_vertices.resize( rings * sectors * 3 + 3 );
    o_normals.resize( rings * sectors * 3 + 3 );
    o_uvs.resize( rings * sectors * 2 + 2 );
    std::vector< GLfloat >::iterator v = o_vertices.begin();
    std::vector< GLfloat >::iterator n = o_normals.begin();
    std::vector< GLfloat >::iterator t = o_uvs.begin();
    for ( r = 0; r < rings; r++ ) {
        for ( s = 0; s < sectors; s++ ) {
            float const y = sin( -M_PI_2 + M_PI * r * R );
            float const x = cos( 2 * M_PI * s * S ) * sin( M_PI * r * R );
            float const z = sin( 2 * M_PI * s * S ) * sin( M_PI * r * R );

            *t++ = s * S;
            *t++ = r * R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            *n++ = -x;
            *n++ = -y;
            *n++ = -z;
        }
    }

    o_indices.resize( rings * sectors * 3 + 3 );
    std::vector< GLuint >::iterator i = o_indices.begin();
    for ( r = 0; r < rings - 1; r++ ) {
        for ( s = 0; s < sectors - 1; s++ ) {
            *i++ = ( r + 1 ) * sectors + s;
            *i++ = ( r + 1 ) * sectors + ( s + 1 );
            *i++ = r * sectors + ( s + 1 );
            *i++ = r * sectors + s;
        }
    }
}

void sphere2( float radius,
             unsigned int rings,
             unsigned int sectors,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLfloat >& o_normals,
             std::vector< GLfloat >& o_uvs,
             std::vector< GLuint >& o_indices ) {

    // North pole
    o_vertices.push_back( 0 );
    o_vertices.push_back( radius );
    o_vertices.push_back( 0 );
    o_normals.push_back( 0 );
    o_normals.push_back( 1 );
    o_normals.push_back( 0 );
    o_uvs.push_back( 0 );
    o_uvs.push_back( 0 );

    float phiStep = 2.0 * M_PI / rings;
    float thetaStep = 2.0f * M_PI / sectors;

    for (int i = 1; i <= rings - 1; ++i) {
        float phi = i * phiStep;
        for (int j = 0; j <= sectors; ++j) {
            float theta = j * thetaStep;

            o_vertices.push_back( radius*sin(phi)*cos(theta) );
            o_vertices.push_back( radius*cos(phi) );
            o_vertices.push_back( radius* sin(phi)*sin(theta));

            o_normals.push_back( -radius*sin(phi)*cos(theta) );
            o_normals.push_back( -radius*cos(phi) );
            o_normals.push_back( -radius* sin(phi)*sin(theta));

            o_uvs.push_back(theta / (M_PI * 2));
            o_uvs.push_back(phi / M_PI);
        }
    }
    
    // South pole
    o_vertices.push_back( 0 );
    o_vertices.push_back( -radius );
    o_vertices.push_back( 0 );
    o_normals.push_back( 0 );
    o_normals.push_back( -1 );
    o_normals.push_back( 0 );
    o_uvs.push_back( 0 );
    o_uvs.push_back( 1 );

    // Indices
    for (int i = 1; i <= sectors; ++i) {
        o_indices.push_back(0);
        o_indices.push_back(i + 1);
        o_indices.push_back(i);
    }

    int baseIndex = 1;
    int ringVertexCount = sectors + 1;
    for (int i = 0; i < rings - 2; ++i) {
        for (int j = 0; j < sectors; ++j) {
            o_indices.push_back(baseIndex + i*ringVertexCount + j);
            o_indices.push_back(baseIndex + i*ringVertexCount + j + 1);
            o_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);

            o_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
            o_indices.push_back(baseIndex + i*ringVertexCount + j + 1);
            o_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
        }
    }
    int southPoleIndex = o_vertices.size() - 1;
    baseIndex = southPoleIndex - ringVertexCount;
    for (int i = 0; i < sectors; ++i) {
        o_indices.push_back(southPoleIndex);
        o_indices.push_back(baseIndex + i);
        o_indices.push_back(baseIndex + i + 1);
    }
}

} // namespace graphics

} // namespace concussion
