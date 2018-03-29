#include <CBase/log.hh>
#include <CBase/assert.hh>
#include <CBase/resource.hh>
#include <CGraphics/shader.hh>
#include <CGame/entity/manager.hh>

#include "application.hh"

class Player {
public:
    Player( const std::string& name ) : m_name( name ) {}
    std::string name() const { return m_name; }
private:
    std::string m_name;
};

int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();

//    concussion::Application app;
//    app.run();

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

