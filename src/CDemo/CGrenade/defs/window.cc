//
// Created by Eddie Hoyle on 19/02/18.
//

#include "window.hh"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <CBase/log.hh>

namespace concussion {

static const int WIDTH = 640;
static const int HEIGHT = 480;

Window::Window()
        : m_handle( nullptr ) {

    if ( !glfwInit() ) {
        CNC_ERROR << "glfw failed to initialise!";
        return;
    }

    m_handle = glfwCreateWindow( WIDTH, HEIGHT, CNC_TARGET_NAME, nullptr, nullptr );
    if ( m_handle == nullptr ) {
        CNC_ERROR << "Failed to create glfw window.";
        return;
    }

    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );

    // Set some defaults
    glfwSwapInterval( 1 );
    glfwSetTime( 0.0 );
    glfwMakeContextCurrent( m_handle );
    glfwSetInputMode( m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL );

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if ( !glewInit() ) {
        CNC_ERROR << "Failed to initialize GLEW";
        glfwDestroyWindow( m_handle );
        return;
    }
}

bool Window::is_open() {
    return glfwWindowShouldClose( m_handle ) == GLFW_FALSE;
}

void Window::update_begin() {
    glfwPollEvents();
}

void Window::update( double elapsed ) {
    glfwSetWindowTitle( m_handle, std::to_string( 1000.0/elapsed ).c_str() );
}

void Window::update_end() {
    glfwSwapBuffers( m_handle );
//}
//
//void Window::run() {
//
//    double time = glfwGetTime();
//    double last_time = time;
//    double frame_timer = 0.0;
//
//    while( !glfwWindowShouldClose( m_handle ) ) {
//
//        double time = glfwGetTime();
//        double elapsed = time - last_time;
//        last_time = time;
//
//        glfwPollEvents();
//
////        processEvents( deltaTime );
////        update( deltaTime );
////        render( deltaTime );
//
//        glfwSwapBuffers( m_handle );
//
//        ++m_frames;
//        frame_timer += elapsed;
//
//        if( frame_timer > 1.0f ) {
//            m_frames = 0;
//            frame_timer = 0.0;
//        }
//    }
//
//}

Window::~Window() {
    glfwDestroyWindow( m_handle );
    glfwTerminate();
}

Window& window() {
    static Window window;
    return window;
}

}