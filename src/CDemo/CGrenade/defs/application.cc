#include "application.hh"
#include "window.hh"

#include <CBase/log.hh>
#include <CGraphics/shader.hh>
#include <CBase/resource.hh>
#include <CBase/io.hh>
#include <CBase/assert.hh>
#include <CGraphics/manager.hh>
#include <CGraphics/buffer.hh>
#include <CGraphics/mesh.hh>
#include <CBase/input.hh>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <cmath>
#include <sstream>

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

    Update update;
    bool tap = false;

    double value = 0.0;

    glm::mat4 model = glm::translate( glm::mat4( 1 ), glm::vec3( 1, 0, 0 ) );

    while ( m_window->open() ) {

        m_window->update_begin( &update );

        if ( update.pressed ) {
            CNC_ERROR << "click=("
                      << update.position.x << ", "
                      << update.position.y << ")";



            glm::vec2 device;
            m_window->to_device_coords( update.position.x, update.position.y,
                                        device.x, device.y );
            glm::mat4 inv_projection = glm::inverse( projection );
            glm::vec4 eye = inv_projection * glm::vec4( device.x, device.y, -1.0f, 1.0f );
            glm::mat4 inv_view = glm::inverse( view );
            glm::vec4 ray = inv_view * eye;
            glm::vec3 n_ray = glm::normalize( glm::vec3( ray.x, ray.y, ray.z ) );
            model = glm::translate( glm::mat4( 1 ), glm::vec3( ray.x, ray.y, 0.0 ) );
            CNC_ERROR << model[3][0] << ", " << model[3][1];
        }
        tap = update.pressed;

        update.time = m_window->time();

        ShaderManager::instance()->bind( "simple" );
        ShaderManager::instance()->load( "u_projectionMatrix", projection );
        ShaderManager::instance()->load( "u_viewMatrix", view );
        ShaderManager::instance()->load( "u_modelMatrix", model );

        glBindVertexArray( vao );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glDrawElements( GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glBindVertexArray( 0 );

        ShaderManager::instance()->unbind();

        elapsed = m_window->time() - update.time;
        if ( ( second += elapsed ) > refresh_rate ) {
            std::stringstream ss;
            ss << "FPS: ";
            ss << second / elapsed * ( 1.0 / refresh_rate );
            m_window->set_title( ss.str() );
            second = 0.0;
        }
        m_window->update_end();

    }
}

}