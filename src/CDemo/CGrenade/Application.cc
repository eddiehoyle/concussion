#include "Application.hh"
#include "Window.hh"

#include <CEngine/Log.hh>
#include <CEngine/graphics/Shader.hh>
#include <CEngine/Resource.hh>
#include <CEngine/IO.hh>
#include <CEngine/Assert.hh>
#include <CEngine/graphics/ShaderManager.hh>
#include <CEngine/graphics/Buffer.hh>
#include <CEngine/graphics/Intersect.hh>
#include <CEngine/graphics/Mesh.hh>
#include <CEngine/Input.hh>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <cmath>
#include <sstream>
#include <CEngine/graphics/Shape.hh>
#include <CEngine/Model.hh>
#include <CEngine/graphics/Cube.hh>
#include <CEngine/graphics/Render.hh>

namespace concussion {

Application::Application()
        : m_window( nullptr ) {
    m_window = std::unique_ptr< Window >( new Window() );
}

//// t: current time, b: begInnIng value, c: change In value, d: duration
//float easeIn( float time, float start, float step, float duration ) {
//    return step*(time/=duration)*time*time*time*time + start;
//}
//
//float easeOut( float time, float start, float step, float duration ) {
//    return step*((time=time/duration-1)*time*time*time*time + 1) + start;
//}
//
//float easeOutExp(float t,float b , float c, float d) {
//    return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
//}

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

    // -------------------------------------------------------------------- //

    std::shared_ptr< Cube > aimer( new Cube );
    std::shared_ptr< Cube > grenade( new Cube );
//    Cube grenade;

    // -------------------------------------------------------------------- //

    // Generate a mesh
    graphics::Shape grid_shape;
    square( 1.0f, grid_shape.vertices, grid_shape.indices, grid_shape.uvs );

    // Buffer mesh
    GLuint grid_vao;
    grid_vao = create_vao();
    bind_vao( grid_vao );
    buffer_indices( grid_shape.indices );
    buffer_data( 0, 3, grid_shape.vertices );
    buffer_data( 1, 2, grid_shape.uvs );
    unbind_vao();

    // ------------------------------------------------------------ //

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

    glm::mat4 sphere_rotate = glm::mat4( 1 );
    glm::mat4 sphere_scale = glm::scale( glm::mat4( 1 ), glm::vec3( 5, 5, 5 ) );
    glm::mat4 sphere_model( 1 );

    bool is_thrown = false;
    double scale = 3.0;

    glm::vec2 tap_press;
    glm::vec2 tap_release;
    glm::vec2 origin( m_window->width() / 2, m_window->height() / 2 );

    double grenade_velocity = 120.0;
    double gravity = 9.8; // Low gravity
    double rotation_velocity = 150.0;
    double rotation_speed = 0;

    StaticRender render;

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

        if ( !tap && update.pressed ) {
            tap_press = update.position;
            is_thrown = false;
        }

        if ( tap && !update.pressed ) {

            tap_release = update.position;
            double length = glm::length( tap_release - origin );
            if ( length > 10 ) {
                glm::vec2 diff( tap_release - origin );
                double angle = std::atan2( diff.y, diff.x );

                grenade_translate = glm::mat4( 1 );
                grenade_move = glm::vec3( diff.x, diff.y, 0.0 ) / length * elapsed * grenade_velocity;
                grenade_rotate = glm::rotate( glm::mat4( 1 ), (float)angle, glm::vec3(0, 0, 1));

                int sign = diff.x > 0 ? -1 : 1;
                rotation_speed = 0;
                rotation_speed = rotation_velocity * elapsed * sign;

                is_thrown = true;
            }
        }
        tap = update.pressed;

        if ( is_thrown ) {
            grenade_move.y -= gravity * elapsed;
        }

        grenade_translate *= glm::translate( glm::mat4( 1 ), grenade_move );
        glm::mat4 grenade_rotate_x = glm::rotate( glm::mat4( 1 ), ( float )elapsed * 10.0f, glm::vec3( 1, 0, 0 ) );
        glm::mat4 grenade_rotate_y = glm::rotate( glm::mat4( 1 ), 0.0f, glm::vec3( 0, 1, 0 ) );
        glm::mat4 grenade_rotate_z = glm::rotate( glm::mat4( 1 ), glm::radians( (float)rotation_speed ), glm::vec3( 0, 0, 1 ) );
        grenade_rotate *= ( grenade_rotate_x * grenade_rotate_y * grenade_rotate_z );
        grenade_scale = glm::scale( glm::mat4( 1 ), glm::vec3( scale, scale, scale ) );
        grenade_model = grenade_translate * grenade_rotate * grenade_scale;

        glm::mat4 grid_scale = glm::scale( glm::mat4( 1 ), glm::vec3( 1, 1, 1 ) * 20.0 );
        glm::mat4 grid_rotate = glm::rotate( glm::mat4( 1 ), glm::radians( 90.0f ), glm::vec3(0, 0, 1));
        glm::mat4 grid_translate = glm::translate( glm::mat4( 1 ), glm::vec3( 0, 0, 0 ) );
        glm::mat4 grid_model = grid_scale * grid_rotate * grid_translate;

        ShaderManager::instance()->bind( "grenade" );
        ShaderManager::instance()->load( "u_projection", projection );
        ShaderManager::instance()->load( "u_view", view );

        if ( update.pressed ) {
            glm::vec2 diff( update.position - origin );
            double angle = std::atan2( diff.y, diff.x );
            glm::mat4 sphere_rotate_x = glm::rotate( glm::mat4( 1 ), ( float )value, glm::vec3( 1, 0, 0 ) );
            glm::mat4 sphere_rotate_y = glm::rotate( glm::mat4( 1 ), 0.0f, glm::vec3( 0, 1, 0 ) );
            glm::mat4 sphere_rotate_z = glm::rotate( glm::mat4( 1 ), ( float )angle, glm::vec3( 0, 0, 1 ) );
            sphere_rotate = sphere_rotate_x * sphere_rotate_y * sphere_rotate_z;
            sphere_model = sphere_rotate * sphere_scale;

            ShaderManager::instance()->load( "u_model", sphere_model );

            render.buffer( aimer );
            render.draw();
        }

        ShaderManager::instance()->load( "u_model", grenade_model );

        render.buffer( grenade );
        render.draw();

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
        glDrawElements( GL_TRIANGLES, grid_shape.indices.size(), GL_UNSIGNED_INT, 0 );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glBindVertexArray( 0 );

        glDisable( GL_BLEND );

        ShaderManager::instance()->unbind();

        m_window->update_end();

    }

//    delete sphere_indices_buffer;
//    delete sphere_vertices_buffer;
//    delete sphere_normals_buffer;
//    delete sphere_uvs_buffer;
}

}