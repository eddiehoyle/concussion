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

    ShaderManager::instance()->add( source );

    while ( m_window->open() ) {

        double start = m_window->time();

        m_window->update_begin();
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