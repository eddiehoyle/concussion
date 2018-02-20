#include <CBase/log.hh>
#include <CBase/assert.hh>

#include "application.hh"

int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();

    int* x = nullptr;

    CNC_ASSERT( x != nullptr );

    concussion::Application app;
    app.run();

    return 0;
}