#include <CBase/log.hh>
#include <CBase/assert.hh>
#include <CBase/resource.hh>
#include <CGraphics/shader.hh>

#include "application.hh"

int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();

    // Initialise window and glew
    concussion::Application app;
    app.run();

    return 0;
}