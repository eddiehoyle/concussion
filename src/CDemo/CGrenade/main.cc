#include "Grenade.hh"
#include "Backpack.hh"
#include "Application.hh"

#include <CEngine/Log.hh>
#include <CEngine/Assert.hh>
#include <CEngine/Entity.hh>
#include <CEngine/graphics/Shader.hh>
#include <CEngine/EntityManager.hh>



int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();

//    concussion::Application app;
//    app.run();

    using namespace concussion;

    EntityManager manager;

    EntityID a = manager.create< Grenade >();
    Grenade* ga = manager.get< Grenade >( a );
    CNC_ASSERT( ga != nullptr );
    CNC_ERROR << ga->getTypeID() << ", " << ga->getID();
    manager.destroy< Grenade >( a );
    CNC_ERROR << (*ga).getTypeID() << ", " << (*ga).getID();

    return 0;
}

