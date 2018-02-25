#include <sstream>
#include <CBase/log.hh>
#include <CGraphics/shader.hh>
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

    while ( m_window->open() ) {

        double start = m_window->time();

        m_window->update_begin();
//        concussion::graphics::SimpleShader shader;
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