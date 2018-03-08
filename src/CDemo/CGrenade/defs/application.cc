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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <cmath>
#include <sstream>

namespace concussion {

Application::Application()
        : m_window( nullptr ) {
    m_window = std::unique_ptr< Window >( new Window() );
}

// t: current time, b: begInnIng value, c: change In value, d: duration
float easeIn( float time, float start, float step, float duration ) {
    return step*(time/=duration)*time*time*time*time + start;
}

float easeOut( float time, float start, float step, float duration ) {
    return step*((time=time/duration-1)*time*time*time*time + 1) + start;
}

float easeOutExp(float t,float b , float c, float d) {
    return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
}

void Application::run() {

    double elapsed = 0.0;
    double second = 0.0;
    double refresh_rate = 1.0;

    using namespace concussion::graphics;

    bool vertex_shader_exists;
    bool fragment_shader_exists;

    const std::string grenade_vertex_path = io::find_resource( "shaders/grenade.vert", vertex_shader_exists );
    CNC_ASSERT( vertex_shader_exists );
    const std::string grenade_vertex_source = io::read_file( grenade_vertex_path );

    const std::string grenade_fragment_path = io::find_resource( "shaders/grenade.frag", fragment_shader_exists );
    CNC_ASSERT( fragment_shader_exists );
    const std::string grenade_fragment_source = io::read_file( grenade_fragment_path );

    const std::string grid_vertex_path = io::find_resource( "shaders/grid_vertex.glsl", vertex_shader_exists );
    CNC_ASSERT( vertex_shader_exists );
    const std::string grid_vertex_source = io::read_file( grid_vertex_path );

    const std::string grid_fragment_path = io::find_resource( "shaders/grid_fragment.glsl", fragment_shader_exists );
    CNC_ASSERT( fragment_shader_exists );
    const std::string grid_fragment_source = io::read_file( grid_fragment_path );

    ShaderSource grenade_source;
    grenade_source.name = "grenade";
    grenade_source.vertex = grenade_vertex_source.c_str();
    grenade_source.fragment = grenade_fragment_source.c_str();
    grenade_source.attributes = { "i_position", "i_uv" };
    grenade_source.uniforms = { "u_projection", "u_view", "u_model" };

    ShaderSource grid_source;
    grid_source.name = "grid";
    grid_source.vertex = grid_vertex_source.c_str();
    grid_source.fragment = grid_fragment_source.c_str();
    grid_source.attributes = { "i_position", "i_uv" };
    grid_source.uniforms = { "u_projectionMatrix", "u_viewMatrix", "u_modelMatrix" };

    ShaderManager::instance()->compile( grenade_source );
    ShaderManager::instance()->compile( grid_source );

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
    glm::mat4 view = glm::lookAt( glm::vec3( 0, 0, 0 ), glm::vec3( 0, 0, 1 ), glm::vec3( 0, 1, 0 ) );
//    glm::mat4 view = glm::translate( glm::mat4( 1 ), glm::vec3( 0, 0, -3.0 ) );


    Update update;
    bool tap = false;

    double value = 0.0;


    glm::mat4 grenade_translate = glm::translate( glm::mat4( 1 ), glm::vec3( 0, 0, 0 ) );
    glm::mat4 grenade_scale = glm::scale( glm::mat4( 1 ), glm::vec3( 1, 1, 1 ) );
    glm::mat4 grenade_model = glm::translate( glm::mat4( 1 ), glm::vec3( 1, 0, 0 ) );
    glm::mat4 grid_model = glm::rotate( glm::mat4( 1 ), 90.0f, glm::vec3( 0.0f, 0.0f, 0.0f ) );

    bool exploding = false;
    double explode_time = 0.0;
    double scale = 0.0;

    while ( m_window->open() ) {

        m_window->update_begin( &update );

        value += 0.03;
        view = glm::lookAt( glm::vec3( 0, 0, -(std::sin( value ) - 3 ) * 5 ), glm::vec3( 0, 0, 1 ), glm::vec3( 0, 1, 0 ) );

        if ( exploding ) {
            explode_time += elapsed;
//            scale = easeIn( explode_time, 0.0, 1000000, 1.0 );
//            scale = easeOut( explode_time, 0.0, 300, 3.0 );
            scale = easeOutExp( explode_time, 0.0, 100, 0.2 );
//            CNC_ERROR << "scale=" << scale;
            if ( scale >= 3 ) {
                scale = 0.0;
                explode_time = 0.0;
                exploding = false;
            }
        }

        if ( tap && !update.pressed ) {

            if ( exploding ) {
                scale = 0.0;
                explode_time = 0.0;
            }

            exploding = true;

            glm::vec2 device;
            m_window->to_device_coords( update.position.x, update.position.y,
                                        device.x, device.y );
            glm::vec4 eye = glm::inverse( projection ) * glm::vec4( device.x, device.y, 1.0f, 1.0f );

            glm::mat4 i_view = glm::inverse( view );
            glm::vec3 cam_ray = glm::normalize( glm::vec3( 0, 0, -view[3].z ) );
            glm::vec3 tap_ray = glm::normalize( glm::vec3( i_view * eye ) );

            double dot = glm::dot( cam_ray, tap_ray );
            double angle_rad = std::acos( dot );
            double angle_deg = glm::degrees( std::acos( dot ) );
            double adjacent = cam_ray.z;
            double opposite = std::tan( angle_rad ) * adjacent;
            double hypotenuse = std::sqrt( std::pow( adjacent, 2 ) + std::pow( opposite, 2 ) );
            double scalar = hypotenuse * -view[3].z;

            glm::vec3 position( glm::vec3( 0, 0, -view[3].z ) + ( tap_ray * scalar ) );
            position.z = 0.0;

            grenade_translate = glm::translate( glm::mat4( 1 ), position );

        }
        tap = update.pressed;

        grenade_scale = glm::scale( glm::mat4( 1 ), glm::vec3( scale, scale, 1.0 ) );
        grenade_model = grenade_translate * grenade_scale;

        float scale = 5.0;
        glm::mat4 grid_scale = glm::scale( glm::mat4( 1 ), glm::vec3( 1, 1, 1 ) * scale );
        glm::mat4 grid_rotate( 1 );
        glm::mat4 grid_translate = glm::translate( glm::mat4( 1 ), glm::vec3( 0, std::sin( 0 ), 0 ) );
        glm::mat4 grid_model = grid_scale * grid_rotate * grid_translate;

        update.time = m_window->time();

        ShaderManager::instance()->bind( "grenade" );
        ShaderManager::instance()->load( "u_projection", projection );
        ShaderManager::instance()->load( "u_view", view );
        ShaderManager::instance()->load( "u_model", grenade_model );

        glBindVertexArray( circle_vao );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glDrawElements( GL_TRIANGLES, circle_vertices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glBindVertexArray( 0 );

        ShaderManager::instance()->unbind();

        ShaderManager::instance()->bind( "grid" );
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