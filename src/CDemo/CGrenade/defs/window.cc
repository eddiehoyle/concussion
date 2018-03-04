#include "window.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <CBase/log.hh>

#include <sstream>
#include <CBase/assert.hh>
#include <CBase/input/manager.hh>

namespace concussion {

static const int WIDTH = 640;
static const int HEIGHT = 480;

void keyboard_callback( GLFWwindow *window, int key, int scancode, int type, int mods ) {
    if ( key == GLFW_KEY_ESCAPE && type == GLFW_PRESS ) {
        glfwSetWindowShouldClose( window, GLFW_TRUE );
        return;
    }
    CNC_ERROR << key;
}


void mouse_button_callback( GLFWwindow* window, int button, int type, int mods ) {

    InputState state = InputState::None;
    switch ( type ) {
        case GLFW_PRESS:
            state = InputState::Press;
            break;
        case GLFW_RELEASE:
            state = InputState::Release;
            break;
    }

    CNC_ASSERT( state != InputState::None );

//    InputAction action = InputAction::None;
//    switch ( button ) {
//        case GLFW_MOUSE_BUTTON_LEFT:
//            action = InputAction::LMB;
//            break;
//        case GLFW_MOUSE_BUTTON_RIGHT:
//            action = InputAction::RMB;
//            break;
//    }
//
//
//    if ( action != InputAction::None && state != InputState::None ) {
//        InputManager::instance()->add( new InputCommand( action, state ) );
//    }
}

Window::Window()
        : m_handle( nullptr ),
          m_initialised( false ) {

    if ( !glfwInit() ) {
        CNC_ERROR << "glfw failed to initialise!";
        return;
    }

    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // To make MacOS happy; should not be needed
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );

    m_handle = glfwCreateWindow( WIDTH, HEIGHT, CNC_TARGET_NAME, nullptr, nullptr );
    if ( m_handle == nullptr ) {
        CNC_ERROR << "Failed to create glfw window.";
        return;
    }

    // Set some defaults
    glfwMakeContextCurrent( m_handle );
    glfwSwapInterval( 1 );
    glfwSetTime( 0.0 );

    glfwSetKeyCallback( m_handle, keyboard_callback );
    glfwSetMouseButtonCallback( m_handle, mouse_button_callback );

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if ( glewInit() != GLEW_OK ) {
        CNC_ERROR << "Failed to initialize GLEW";
        glfwDestroyWindow( m_handle );
        return;
    }

    // Good to go
    m_initialised = true;
}

bool Window::open() const {
    CNC_ASSERT( m_initialised );
    return !glfwWindowShouldClose( m_handle );
}

void Window::set_title( const std::string& title ) {
    CNC_ASSERT( m_initialised );
    glfwSetWindowTitle( m_handle, title.c_str() );
}

void Window::update_begin() {
    CNC_ASSERT( m_initialised );

    glEnable( GL_DEPTH_TEST );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( 1, 0.5, 0, 1 );

    glfwPollEvents();

    double x, y;
    glfwGetCursorPos( m_handle, &x, &y );
    InputManager::instance()->mouse()->update( x, y );
}

void Window::update_end() {
    CNC_ASSERT( m_initialised );
    glfwSwapBuffers( m_handle );
}

double Window::time() const {
    return m_initialised ? glfwGetTime() : 0.0;
}

Window::~Window() {
    CNC_ASSERT( m_initialised );
    glfwDestroyWindow( m_handle );
    glfwTerminate();
}

}