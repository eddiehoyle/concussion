#include <sstream>
#include <CBase/log.hh>
#include <CGraphics/shader.hh>
#include <CGraphics/domain.hh>
#include <CBase/resource.hh>
#include <CBase/io.hh>
#include <CBase/assert.hh>
#include <CGraphics/manager.hh>
#include "application.hh"

namespace concussion {

Application::Application()
        : m_window( nullptr ) {
    m_window = std::unique_ptr< Window >( new Window() );
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

    GLfloat vertices[12] = {
            -0.5f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f
    };
    GLuint vertices_count = sizeof( vertices ) / sizeof( vertices[0] );
    GLuint vertices_size = sizeof( GLfloat ) * vertices_count;

    GLuint indices[6] = {
            0, 1, 3,
            3, 1, 2
    };
    GLuint indices_count = sizeof( indices ) / sizeof( indices[0] );
    GLuint indices_size = sizeof( GLuint ) * indices_count;

    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, vertices_size, &vertices[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    GLuint ebo;
    glGenBuffers( 1, &ebo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices_size, &indices[0], GL_STATIC_DRAW );

    glBindVertexArray( 0 );

    while ( m_window->open() ) {

        double start = m_window->time();

        m_window->update_begin();

        ShaderManager::instance()->bind( "simple" );

        glBindVertexArray( vao );
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