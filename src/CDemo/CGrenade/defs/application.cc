#include "application.hh"

#include <CBase/log.hh>
#include <CGraphics/shader.hh>
#include <CBase/resource.hh>
#include <CBase/io.hh>
#include <CBase/assert.hh>
#include <CGraphics/manager.hh>
#include <CGraphics/buffer.hh>
#include <CGraphics/mesh.hh>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <cmath>
#include <sstream>
#include <CBase/input/manager.hh>

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
    source.attributes = { "i_position", "i_uv" };
    source.uniforms = { "u_projectionMatrix", "u_viewMatrix", "u_modelMatrix" };

    ShaderManager::instance()->compile( source );

    // Generate a mesh
    std::vector< GLuint > indices;
    std::vector< GLfloat > vertices;
    std::vector< GLfloat > uvs;
    circle( 0.5f, 32, vertices, indices, uvs );

    // Buffer mesh
    GLuint vao;
    vao = create_vao();
    bind_vao( vao );
    buffer_indices( indices );
    buffer_data( 0, 3, vertices );
    buffer_data( 1, 2, uvs );
    unbind_vao();

    // Define some uniforms
    glm::mat4 projection = glm::perspectiveFov( 70.0f, 640.0f, 480.0f, 0.01f, 1000.0f );
    glm::mat4 view = glm::translate( glm::mat4( 1 ), glm::vec3( 0.0f, 0.0f, -3.0f ) );

    double value = 0.0;

    while ( m_window->open() ) {

        m_window->update_begin();

//        const glm::vec2& pos = InputManager::instance()->mouse()->get_position();
//        CNC_ERROR << "pos=" << glm::to_string( pos );

        value += 0.03;
        double start = m_window->time();

        ShaderManager::instance()->bind( "simple" );
        ShaderManager::instance()->load( "u_projectionMatrix", projection );
        ShaderManager::instance()->load( "u_viewMatrix", view );

        glm::mat4 model = glm::translate( glm::mat4( 1 ), glm::vec3( std::sin( value ), std::cos( value ), 0.0f ) );
        ShaderManager::instance()->load( "u_modelMatrix", model );

        glBindVertexArray( vao );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glDrawElements( GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
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