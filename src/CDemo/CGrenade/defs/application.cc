#include "application.hh"
#include "window.hh"

#include <CBase/log.hh>
#include <CGraphics/shader.hh>
#include <CBase/resource.hh>
#include <CBase/io.hh>
#include <CBase/assert.hh>
#include <CGraphics/manager.hh>
#include <CGraphics/buffer.hh>
#include <CGraphics/intersect.hh>
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

    const std::string grid_vertex_path = io::find_resource( "shaders/grid.vert", vertex_shader_exists );
    CNC_ASSERT( vertex_shader_exists );
    const std::string grid_vertex_source = io::read_file( grid_vertex_path );

    const std::string grid_fragment_path = io::find_resource( "shaders/grid.frag", fragment_shader_exists );
    CNC_ASSERT( fragment_shader_exists );
    const std::string grid_fragment_source = io::read_file( grid_fragment_path );

    ShaderSource grenade_source;
    grenade_source.name = "grenade";
    grenade_source.vertex = grenade_vertex_source.c_str();
    grenade_source.fragment = grenade_fragment_source.c_str();
    grenade_source.attributes = { "i_position", "i_normal", "i_uv" };
    grenade_source.uniforms = { "u_projection", "u_view", "u_model" };

    ShaderSource grid_source;
    grid_source.name = "grid";
    grid_source.vertex = grid_vertex_source.c_str();
    grid_source.fragment = grid_fragment_source.c_str();
    grid_source.attributes = { "i_position", "i_uv" };
    grid_source.uniforms = { "u_projection", "u_view", "u_model" };

    ShaderManager::instance()->compile( grenade_source );
    ShaderManager::instance()->compile( grid_source );

//    // Generate a mesh
//    std::vector< GLfloat > grenade_vertices;
//    std::vector< GLuint > grenade_indices;
//    std::vector< GLfloat > grenade_uvs;
//    circle( 0.5f, 32, grenade_vertices, grenade_indices, grenade_uvs );

    // Generate a mesh
    std::vector< GLfloat > grenade_vertices;
    std::vector< GLfloat > grenade_normals;
    std::vector< GLfloat > grenade_uvs;
    std::vector< GLuint > grenade_indices;
//    sphere( 1.0f, 16, 16, grenade_vertices, grenade_normals, grenade_uvs, grenade_indices );
    cube( 1.0f, grenade_vertices, grenade_normals, grenade_uvs, grenade_indices );

    // Buffer mesh
    GLuint grenade_vao;
    grenade_vao = create_vao();
    bind_vao( grenade_vao );
    buffer_indices( grenade_indices );
    buffer_data( 0, 3, grenade_vertices );
    buffer_data( 1, 3, grenade_normals );
    buffer_data( 2, 2, grenade_uvs );
    unbind_vao();

    // Generate a mesh
    std::vector< GLfloat > direction_vertices;
    std::vector< GLfloat > direction_normals;
    std::vector< GLfloat > direction_uvs;
    std::vector< GLuint > direction_indices;
//    sphere( 1.0f, 16, 16, direction_vertices, direction_normals, direction_uvs, direction_indices );
    sphere( 1.0f, direction_vertices, direction_normals, direction_uvs, direction_indices );

    // Buffer mesh
    GLuint direction_vao;
    direction_vao = create_vao();
    bind_vao( direction_vao );
    buffer_indices( direction_indices );
    buffer_data( 0, 3, direction_vertices );
    buffer_data( 1, 3, direction_normals );
    buffer_data( 2, 2, direction_uvs );
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
    glm::mat4 projection = glm::perspectiveFov( 70.0f, 640.0f, 480.0f, 1.0f, 1000.0f );

    Update update;
    bool tap = false;

    double value = 0.0;

    glm::mat4 grenade_translate = glm::mat4( 1 );
    glm::mat4 grenade_rotate = glm::mat4( 1 );
    glm::mat4 grenade_scale = glm::scale( glm::mat4( 1 ), glm::vec3( 1, 1, 1 ) );
    glm::mat4 grenade_model = glm::translate( glm::mat4( 1 ), glm::vec3( 1, 0, 0 ) );
    glm::vec3 grenade_move;

    glm::mat4 direction_rotate = glm::mat4( 1 );
    glm::mat4 direction_scale = glm::scale( glm::mat4( 1 ), glm::vec3( 5, 5, 5 ) );
    glm::mat4 direction_model( 1 );

    bool is_thrown = false;
    double scale = 3.0;

    glm::vec2 tap_press;
    glm::vec2 tap_release;

    double grenade_velocity = 120.0;
    double gravity = 4.8; // Low gravity
    double rotation_velocity = 150.0;
    double rotation_speed = 0;

    while ( m_window->open() ) {

        elapsed = m_window->time() - update.time;
        if ( ( second += elapsed ) > refresh_rate ) {
            std::stringstream ss;
            ss << "FPS: ";
            ss << second / elapsed * ( 1.0 / refresh_rate );
            m_window->set_title( ss.str() );
            second = 0.0;
        }

        m_window->update_begin( &update );

        value += 0.03;

        float sin_zoom = -(std::sin( value ) - 3 ) * 25 + 25;
        glm::mat4 view = glm::lookAt( glm::vec3( 0, 0, 80 ), glm::vec3( 0, 0, 1 ), glm::vec3( 0, 1, 0 ) );

//        if ( update.pressed ) {
//
//            const glm::vec3 ray_world = compute_world_ray( m_window->viewport(),
//                                                           update.position,
//                                                           view,
//                                                           projection );
//
//            glm::vec3 intersection( 0, 0, 0 );
//            rayPlaneIntersect( glm::vec3( 0, 0, 0 ),
//                               glm::vec3( 0, 0, -1 ),
//                               glm::vec3( -view[3] ),
//                               ray_world,
//                               &intersection );
//
//            grenade_translate = glm::translate( glm::mat4( 1 ), intersection );
//
//        }
//        tap = update.pressed;

        if ( !tap && update.pressed ) {
            tap_press = update.position;
            is_thrown = false;
        }



        if ( tap && !update.pressed ) {

            tap_release = update.position;
//            CNC_ERROR << "position=" << glm::to_string( update.position );
//            CNC_ERROR << "press=" << glm::to_string( tap_press );
//            CNC_ERROR << "release=" << glm::to_string( tap_release );

            double length = glm::length( tap_release - tap_press );
            if ( length > 10 ) {
                glm::vec2 diff( tap_release - tap_press );
                double angle = std::atan2( diff.y, diff.x );
                CNC_ERROR << glm::degrees( angle );

                grenade_translate = glm::mat4( 1 );
                grenade_move = glm::vec3( diff.x, diff.y, 0.0 ) / length * elapsed * grenade_velocity;
                grenade_rotate = glm::rotate( glm::mat4( 1 ), (float)angle, glm::vec3(0, 0, 1));

                int sign = diff.x > 0 ? -1 : 1;
                rotation_speed = 0;
                rotation_speed = rotation_velocity * elapsed * sign;
                CNC_ERROR << rotation_velocity;

                is_thrown = true;

                direction_rotate = glm::rotate( glm::mat4( 1 ), (float)angle, glm::vec3(0, 0, 1));

            }
        }
        tap = update.pressed;

        if ( is_thrown ) {
            grenade_move.y -= gravity * elapsed;
        }

        grenade_translate *= glm::translate( glm::mat4( 1 ), grenade_move );
        grenade_rotate *= glm::rotate( glm::mat4( 1 ), glm::radians( (float)rotation_speed ), glm::vec3(0, 0, 1));
        grenade_scale = glm::scale( glm::mat4( 1 ), glm::vec3( scale, scale, scale ) );
        grenade_model = grenade_translate * grenade_rotate * grenade_scale;

        glm::mat4 grid_scale = glm::scale( glm::mat4( 1 ), glm::vec3( 1, 1, 1 ) * 20.0 );
        glm::mat4 grid_rotate = glm::rotate( glm::mat4( 1 ), glm::radians( 90.0f ), glm::vec3(0, 0, 1));
        glm::mat4 grid_translate = glm::translate( glm::mat4( 1 ), glm::vec3( 0, 0, 0 ) );
        glm::mat4 grid_model = grid_scale * grid_rotate * grid_translate;

        glm::mat4 direction_model = direction_rotate * direction_scale;

        update.time = m_window->time();

        ShaderManager::instance()->bind( "grenade" );
        ShaderManager::instance()->load( "u_projection", projection );
        ShaderManager::instance()->load( "u_view", view );
        ShaderManager::instance()->load( "u_model", direction_model );

        glBindVertexArray( direction_vao );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glEnableVertexAttribArray( 2 );
        glDrawElements( GL_TRIANGLES, direction_indices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glDisableVertexAttribArray( 2 );
        glBindVertexArray( 0 );


//        ShaderManager::instance()->bind( "grenade" );
//        ShaderManager::instance()->load( "u_projection", projection );
//        ShaderManager::instance()->load( "u_view", view );
        ShaderManager::instance()->load( "u_model", grenade_model );

        glBindVertexArray( grenade_vao );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glEnableVertexAttribArray( 2 );
        glDrawElements( GL_TRIANGLES, grenade_indices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glDisableVertexAttribArray( 2 );
        glBindVertexArray( 0 );


        ShaderManager::instance()->unbind();

        ShaderManager::instance()->bind( "grid" );
        ShaderManager::instance()->load( "u_projection", projection );
        ShaderManager::instance()->load( "u_view", view );
        ShaderManager::instance()->load( "u_model", grid_model );

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glBindVertexArray( grid_vao );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glDrawElements( GL_TRIANGLES, grid_indices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glBindVertexArray( 0 );

        glDisable( GL_BLEND );

        ShaderManager::instance()->unbind();

        m_window->update_end();

    }
}

}