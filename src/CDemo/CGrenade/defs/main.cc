#include <CBase/log.hh>
#include <CBase/assert.hh>
#include <CBase/resource.hh>
#include <CGraphics/shader.hh>
#include <CGame/entity/manager.hh>

#include "application.hh"

class Player {
public:
    Player( int x ) : m_x( x ) {}
private:
    int m_x;
};

int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();

//    concussion::Application app;
//    app.run();

    concussion::EntityManager manager;
    int a = manager.create< Player >( 123 );
    int b = manager.create< Player >( 123 );
    int c = manager.create< Player >( 123 );
    int d = manager.create< Player >( 123 );
    CNC_ERROR << "a: " << a;
    CNC_ERROR << "b: " << b;
    CNC_ERROR << "c: " << c;
    CNC_ERROR << "d: " << d;

    return 0;
}

