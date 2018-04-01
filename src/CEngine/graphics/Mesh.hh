#ifndef CONCUSSION_MESH_HH
#define CONCUSSION_MESH_HH

#include <GL/glew.h>

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <set>

namespace concussion {

namespace graphics {

/// TODO
void cube( float size,
           std::vector< GLfloat >& o_vertices,
           std::vector< GLfloat >& o_normals,
           std::vector< GLfloat >& o_uvs,
           std::vector< GLuint >& o_indices );

/// TODO
void sphere( float radius,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLfloat >& o_normals,
             std::vector< GLfloat >& o_uvs,
             std::vector< GLuint >& o_indices );

/// Generate a 2D circle mesh (currently drawn via GL_TRIANGLES)
/// The origin point is the center of the circle.
/// @param radius The size of the circle.
/// @param subdivisions The amount of sides on the circle.
/// @param[out] o_vertices The circle vertices.
/// @param[out] o_indices The circle indices
void circle( float radius,
             unsigned int subdivisions,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLuint >& o_indices,
             std::vector< GLfloat >& o_uvs );

/// Generate a 2D square.
/// The origin point is the center of the square.
/// @param size The width and height of the square.
/// @param[out] o_vertices The square vertices/
/// @param[out] o_indices The square indices.
void square( float size,
             std::vector< GLfloat >& o_vertices,
             std::vector< GLuint >& o_indices,
             std::vector< GLfloat >& o_uvs );


class ElementArrayBuffer;
class AttributeArrayBuffer;

class Mesh {
public:
    Mesh();
    virtual ~Mesh();

    virtual void draw() {
        glBindVertexArray( get_vao() );
        for ( const auto& attribute : get_attributes() ) {
            glEnableVertexAttribArray( attribute );
        }
//        glDrawElements( GL_TRIANGLES, aimer.get_indices_count(), GL_UNSIGNED_INT, 0 );
        m_drawFunc( get_indices_count() );
        for ( const auto& attribute : get_attributes() ) {
            glDisableVertexAttribArray( attribute );
        }
        glBindVertexArray( 0 );
    }

    void setDrawFunc( std::function< void( GLuint ) > func ) {
        m_drawFunc = func;
    }

    GLuint get_vao() const;
    GLuint get_indices_count() const;
    std::set< GLuint > get_attributes() const;

    void bind();
    void unbind();
protected:
    void attach( ElementArrayBuffer* buffer );
    void attach( GLuint index, AttributeArrayBuffer* buffer );

    GLuint m_vao;
    GLuint m_count;
    ElementArrayBuffer* m_indices;
    std::map< GLuint, AttributeArrayBuffer* > m_attributes;

    std::function< void( GLuint ) > m_drawFunc;
};

using MeshPtr = std::shared_ptr< Mesh >;


} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_SHADER_HH
