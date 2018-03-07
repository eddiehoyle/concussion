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
void drawSquare()
{

}
void Application::run() {

    double elapsed = 0.0;
    double second = 0.0;
    double refresh_rate = 1.0;

    using namespace concussion::graphics;

    bool vertex_shader_exists;
    bool fragment_shader_exists;

    const std::string simple_vertex_path = io::find_resource( "shaders/simple_vertex.glsl", vertex_shader_exists );
    CNC_ASSERT( vertex_shader_exists );
    const std::string simple_vertex_source = io::read_file( simple_vertex_path );

    const std::string simple_fragment_path = io::find_resource( "shaders/simple_fragment.glsl", fragment_shader_exists );
    CNC_ASSERT( fragment_shader_exists );
    const std::string simple_fragment_source = io::read_file( simple_fragment_path );

    const std::string gui_vertex_path = io::find_resource( "shaders/gui_vertex.glsl", vertex_shader_exists );
    CNC_ASSERT( vertex_shader_exists );
    const std::string gui_vertex_source = io::read_file( gui_vertex_path );

    const std::string gui_fragment_path = io::find_resource( "shaders/gui_fragment.glsl", fragment_shader_exists );
    CNC_ASSERT( fragment_shader_exists );
    const std::string gui_fragment_source = io::read_file( gui_fragment_path );

    ShaderSource simple_source;
    simple_source.name = "simple";
    simple_source.vertex = simple_vertex_source.c_str();
    simple_source.fragment = simple_fragment_source.c_str();
    simple_source.attributes = { "i_position", "i_uv" };
    simple_source.uniforms = { "u_projectionMatrix", "u_viewMatrix", "u_modelMatrix" };

    ShaderSource gui_source;
    gui_source.name = "gui";
    gui_source.vertex = gui_vertex_source.c_str();
    gui_source.fragment = gui_fragment_source.c_str();
    gui_source.attributes = { "i_position", "i_uv" };
    gui_source.uniforms = { "u_projectionMatrix", "u_viewMatrix", "u_modelMatrix" };

    ShaderManager::instance()->compile( simple_source );
    ShaderManager::instance()->compile( gui_source );

    // Generate a mesh
    std::vector< GLfloat > circle_vertices;
    std::vector< GLuint > circle_indices;
    std::vector< GLfloat > circle_uvs;
    circle( 0.5f, 32, circle_vertices, circle_indices, circle_uvs );

    // Buffer mesh
    GLuint circle_vao;
    circle_vao = create_vao();
    bind_vao( circle_vao );
    buffer_indices( circle_indices );
    buffer_data( 0, 3, circle_vertices );
    buffer_data( 1, 2, circle_uvs );
    unbind_vao();

    // Generate a mesh
    std::vector< GLfloat > grid_vertices;
    std::vector< GLuint > grid_indices;
    std::vector< GLfloat > grid_uvs;
    square( 1.0f, grid_vertices, grid_indices, grid_uvs );

    // Buffer mesh
    GLuint grid_vao;
    grid_vao = create_vao();
    bind_vao( grid_vao );
    buffer_indices( grid_indices );
    buffer_data( 0, 3, grid_vertices );
    buffer_data( 1, 2, grid_uvs );
    unbind_vao();

    // Define some uniforms
    glm::mat4 projection = glm::perspectiveFov( 70.0f, 640.0f, 480.0f, 0.01f, 1000.0f );
    glm::mat4 view = glm::lookAt( glm::vec3( 0, 0, -10.0 ), glm::vec3( 0, 0, -1 ), glm::vec3( 0, 1, 0 ) );
//    glm::mat4 view = glm::translate( glm::mat4( 1 ), glm::vec3( 0, 0, -3.0 ) );


    Update update;
    bool tap = false;

    double value = 0.0;

    glm::mat4 circle_model = glm::translate( glm::mat4( 1 ), glm::vec3( 1, 0, 0 ) );
    glm::mat4 grid_model = glm::rotate( glm::mat4( 1 ), 90.0f, glm::vec3( 0.0f, 0.0f, 0.0f ) );

    while ( m_window->open() ) {

        m_window->update_begin( &update );

        value += 0.05;

        if ( tap && !update.pressed ) {
            glm::vec2 device;
            m_window->to_device_coords( update.position.x, update.position.y,
                                        device.x, device.y );
            glm::vec4 eye = glm::inverse( projection ) * glm::vec4( device.x, device.y, -1.0f, 1.0f );
            glm::vec4 ray = glm::normalize( view * eye );
            circle_model = glm::translate( glm::mat4( 1 ), glm::vec3( ray.x, ray.y, 0.0 ) );
            CNC_ERROR << circle_model[3][0] << ", " << circle_model[3][1];
        }
        tap = update.pressed;

        float scale = 5.0;
        glm::mat4 grid_scale = glm::scale( glm::mat4( 1 ), glm::vec3( 1, 1, 1 ) * scale );
        glm::mat4 grid_rotate( 1 );
        glm::mat4 grid_translate = glm::translate( glm::mat4( 1 ), glm::vec3( 0, std::sin( 0 ), 0 ) );
        glm::mat4 grid_model = grid_scale * grid_rotate * grid_translate;

        update.time = m_window->time();

        ShaderManager::instance()->bind( "simple" );
        ShaderManager::instance()->load( "u_projectionMatrix", projection );
        ShaderManager::instance()->load( "u_viewMatrix", view );
        ShaderManager::instance()->load( "u_modelMatrix", circle_model );

        glBindVertexArray( circle_vao );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glDrawElements( GL_TRIANGLES, circle_vertices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glBindVertexArray( 0 );

        ShaderManager::instance()->unbind();

        ShaderManager::instance()->bind( "gui" );
        ShaderManager::instance()->load( "u_projectionMatrix", projection );
        ShaderManager::instance()->load( "u_viewMatrix", view );
        ShaderManager::instance()->load( "u_modelMatrix", grid_model );

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glBindVertexArray( grid_vao );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glDrawElements( GL_TRIANGLES, grid_vertices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glBindVertexArray( 0 );

        glDisable( GL_BLEND );

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