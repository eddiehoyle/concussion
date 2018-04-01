#include <CEngine/Log.hh>
#include <CEngine/Assert.hh>
#include <CEngine/Resource.hh>
#include <CEngine/graphics/Shader.hh>
#include <CEngine/EntityManager.hh>

#include "Application.hh"

//class Player {};

int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();

    concussion::Application app;
    app.run();

    concussion::EntityManager manager;
    int a = manager.create< Player >( "dave" );
    int b = manager.create< Player >( "laura" );
    int c = manager.create< Player >( "butts" );
    int d = manager.create< Player >( "jess" );
    CNC_ERROR << "a: " << a;
    CNC_ERROR << "b: " << b;
    CNC_ERROR << "c: " << c;
    CNC_ERROR << "d: " << d;

    for ( auto i : { a, b, c, d } ) {
        Player* player = manager.get< Player >( i );
        CNC_ERROR << "name: " << player->name();
    }

    manager.destroy< Player >( a );
    manager.destroy< Player >( b);
    manager.destroy< Player >( c );
    manager.destroy< Player >( d );

    return 0;
}

