#include <sstream>
#include "application.hh"

namespace concussion {

Application::Application()
        : m_window( nullptr ) {
    m_window = std::unique_ptr< Window >( new Window() );
}

void Application::run() {

    double elapsed = 0.0;
    double second = 0.0;

    while ( m_window->open() ) {

        double start = m_window->time();

        m_window->update_begin();
        m_window->update_end();

        elapsed = m_window->time() - start;

        if ( ( second += elapsed ) > 1.0 ) {
            std::stringstream ss;
            ss << "FPS: ";
            ss << second / elapsed;
            m_window->set_title( ss.str() );
            second = 0.0;
        }
    }
}

}