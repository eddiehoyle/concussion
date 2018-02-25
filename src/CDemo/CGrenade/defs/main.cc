#include <CBase/log.hh>
#include <CBase/assert.hh>
#include <CBase/resource.hh>
#include <CGraphics/shader.hh>

#include "application.hh"
//
//int main( int argc, const char* argv[] ) {
//
//    CNC_INITIALISE_LOG();
//
//    // Initialise window and glew
//    concussion::Application app;
////    app.run();
//    concussion::graphics::SimpleShader shader;
//
//    return 0;
//}


// Graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++
#include <cstdlib>
#include <cstdio>

void keyPressEvent( GLFWwindow* window, int key, int scancode, int action, int mods ) {
    if ( action != GLFW_PRESS )
        return;
    if ( key == GLFW_KEY_ESCAPE && mods == 0 )
        glfwSetWindowShouldClose( window, GLFW_TRUE );
}

int main( int argc, char **argv ) {

    // Initialise GLFW
    if ( glfwInit() == GLFW_FALSE ) {
        printf( "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // To make MacOS happy; should not be needed
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 640, 480, "01_triangle", nullptr, nullptr );
    if ( window == nullptr ) {
        printf( "Failed to open GLFW window.\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Setup defaults
    glfwSwapInterval( 1 );
    glfwSetTime( 0.0 );

    // Setup callbacks
    glfwSetKeyCallback( window, keyPressEvent );
    glfwSetWindowTitle( window, "01_window" );

    // Activate this context
    glfwMakeContextCurrent( window );

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if ( glewInit() != GLEW_OK ) {
        printf( "Failed to initialize GLEW\n" );
        glfwTerminate();
        return 1;
    }

    // This almost works...!
    concussion::graphics::SimpleShader shader;

//    while ( glfwWindowShouldClose( window ) == 0 ) {
//
//        // Swap buffers
//        glfwSwapBuffers( window );
//        glfwPollEvents();
//    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

