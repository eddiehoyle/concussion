#include <sstream>
#include <CBase/log.hh>
#include <CGraphics/shader.hh>
#include <CBase/resource.hh>
#include <CBase/io.hh>
#include <CBase/assert.hh>
#include <CGraphics/manager.hh>
#include <CGraphics/mesh.hh>
#include <cmath>
#include "application.hh"

namespace concussion {

Application::Application()
        : m_window( nullptr ) {
    m_window = std::unique_ptr< Window >( new Window() );
}

void circle( std::vector< GLfloat >& vertices,
             std::vector< GLuint >& indices ) {

    int sides = 5;
    vertices.push_back( 0.0f );
    vertices.push_back( 0.0f );
    vertices.push_back( 0.0f );

    vertices.push_back( std::cos(1 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( std::sin(1 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( 0.0f );

    vertices.push_back( std::cos(2 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( std::sin(2 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( 0.0f );

    vertices.push_back( std::cos(3 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( std::sin(3 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( 0.0f );

    vertices.push_back( std::cos(4 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( std::sin(4 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( 0.0f );

    vertices.push_back( std::cos(5 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( std::sin(5 * ((2.0f * 3.14159f) / sides)) );
    vertices.push_back( 0.0f );

    indices.push_back( 0 );
    indices.push_back( 1 );
    indices.push_back( 2 );

    indices.push_back( 0 );
    indices.push_back( 2 );
    indices.push_back( 3 );

    indices.push_back( 0 );
    indices.push_back( 3 );
    indices.push_back( 4 );

    indices.push_back( 0 );
    indices.push_back( 4 );
    indices.push_back( 5 );

    indices.push_back( 0 );
    indices.push_back( 5 );
    indices.push_back( 1 );

}

void Application::run() {

    double elapsed = 0.0;
    double second = 0.0;
    double refresh_rate = 1.0;

    using namespace concussion::graphics;

    bool vertex_shader_exists;
    const std::string vertex_path = io::find_resource( "shaders/simple_vertex.glsl", vertex_shader_exists );
    CNC_ASSERT( vertex_shader_exists );
    const std::string vertex_source = io::read_file( vertex_path );

    bool fragment_shader_exists;
    const std::string fragment_path = io::find_resource( "shaders/simple_fragment.glsl", fragment_shader_exists );
    CNC_ASSERT( fragment_shader_exists );
    const std::string fragment_source = io::read_file( fragment_path );

    ShaderSource source;
    source.name = "simple";
    source.vertex = vertex_source.c_str();
    source.fragment = fragment_source.c_str();
    source.attributes = { "i_position" };
    source.uniforms = { "u_modelMatrix", "u_viewMatrix", "u_projectionMatrix" };

    ShaderManager::instance()->compile( source );

    std::vector< GLfloat > _vertices;
    std::vector< GLuint > _indices;
    circle( _vertices, _indices );

    GLfloat vertices[_vertices.size()];
    for ( std::size_t i = 0; i < _vertices.size(); ++i ) {
        vertices[i] = _vertices[i];
    }

    GLuint indices[_indices.size()];
    for ( std::size_t i = 0; i < _indices.size(); ++i ) {
        indices[i] = _indices[i];
    }

//    GLfloat vertices[12] = {
//            -0.5f, 0.5f, 0.0f,
//            -0.5f, -0.5f, 0.0f,
//            0.5f, -0.5f, 0.0f,
//            0.5f, 0.5f, 0.0f
//    };
    GLuint vertices_count = sizeof( vertices ) / sizeof( vertices[0] );
    GLuint vertices_size = sizeof( GLfloat ) * vertices_count;

//    GLuint indices[6] = {
//            0, 1, 3,
//            3, 1, 2
//    };
    GLuint indices_count = sizeof( indices ) / sizeof( indices[0] );
    GLuint indices_size = sizeof( GLuint ) * indices_count;

    Mesh mesh;
    mesh.vao = buffer( vertices, vertices_count, indices, indices_count );

    while ( m_window->open() ) {

        double start = m_window->time();

        m_window->update_begin();

        ShaderManager::instance()->bind( "simple" );

        glBindVertexArray( mesh.vao );
        glEnableVertexAttribArray( 0 );
        glDrawElements( GL_TRIANGLES, vertices_count, GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glBindVertexArray( 0 );

        ShaderManager::instance()->unbind();

        m_window->update_end();

        elapsed = m_window->time() - start;
        if ( ( second += elapsed ) > refresh_rate ) {
            std::stringstream ss;
            ss << "FPS: ";
            ss << second / elapsed * ( 1.0 / refresh_rate );
            m_window->set_title( ss.str() );
            second = 0.0;
        }
    }
}

}