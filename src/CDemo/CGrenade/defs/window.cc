#include "window.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <CBase/log.hh>
#include <sstream>
#include <CBase/assert.hh>
#include <CBase/input.hh>

namespace concussion {

static const int WIDTH = 640;
static const int HEIGHT = 480;

float clamp( float n, float lower, float upper ) {
    return std::max(lower, std::min(n, upper));
}

glm::vec3 compute_world_ray( const glm::vec2& window,
                             const glm::vec2& mouse,
                             const glm::mat4& view,
                             const glm::mat4& projection ) {

    const glm::vec2 device( clamp( ( 2.0f * mouse.x ) / window.x - 1, -1, 1 ),
                            -clamp( ( 2.0f * mouse.y ) / window.y - 1, -1, 1 ) );
    const glm::vec4 ray_clip = glm::inverse( projection ) * glm::vec4( device.x, device.y, -1.0, 1.0 );
    const glm::vec4 ray_eye( ray_clip.x, ray_clip.y, -1.0, 0.0 );
    return glm::normalize( glm::vec3( glm::inverse( view ) * ray_eye ) );
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

void Window::update_begin( Update* input ) {
    CNC_ASSERT( m_initialised );
    CNC_ASSERT( input != nullptr );

    glEnable( GL_DEPTH_TEST );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( 1, 0.5, 0, 1 );

    glfwPollEvents();

    if ( glfwGetKey( m_handle, GLFW_KEY_ESCAPE ) == GLFW_TRUE ) {
        request_quit();
        return;
    };

    // Mouse pos is from bottom left
    double x, y;
    glfwGetCursorPos( m_handle, &x, &y );
    input->position = glm::vec2( x, height() - y );
    input->pressed = glfwGetMouseButton( m_handle, GLFW_MOUSE_BUTTON_1 ) == GLFW_PRESS;
}

void Window::update_end() {
    CNC_ASSERT( m_initialised );
    glfwSwapBuffers( m_handle );
}

double Window::time() const {
    return m_initialised ? glfwGetTime() : 0.0;
}

void Window::request_quit() {
    glfwSetWindowShouldClose( m_handle, GLFW_TRUE );
}

int Window::width() const {
    return viewport().x;
}

int Window::height() const {
    return viewport().y;
}

glm::ivec2 Window::viewport() const {
    glm::ivec2 viewport;
    glfwGetWindowSize( m_handle, &viewport.x, &viewport.y );
    return viewport;
}

//void Window::to_device_coords( int i_x, int i_y, float& o_x, float& o_y ) const {
//    o_x = clamp( ( 2.0f * i_x ) / width() - 1, -1, 1 );
//    o_y = -clamp( ( 2.0f * i_y ) / height() - 1, -1, 1 );
//}

Window::~Window() {
    CNC_ASSERT( m_initialised );
    glfwDestroyWindow( m_handle );
    glfwTerminate();
}

}