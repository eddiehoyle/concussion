#ifndef CONCUSSION_MESH_HH
#define CONCUSSION_MESH_HH

#include <GL/glew.h>

#include <string>
#include <vector>
#include <map>
#include <memory>

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
    GLuint vao() const;
    GLuint count() const;
    void bind();
    void unbind();
protected:
    void attach( ElementArrayBuffer* buffer );
    void attach( GLuint index, AttributeArrayBuffer* buffer );

    GLuint m_vao;
    GLuint m_count;
    ElementArrayBuffer* m_indices;
    std::vector< AttributeArrayBuffer* > m_attributes;
};



} // namespace graphics

} // namespace concussion

#endif // CONCUSSION_SHADER_HH
