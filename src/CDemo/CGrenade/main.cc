#include "Grenade.hh"
#include "Backpack.hh"
#include "Application.hh"

#include <CEngine/Log.hh>
#include <CEngine/Assert.hh>
#include <CEngine/Engine.hh>
#include <CEngine/EntityManager.hh>

#include <memory>


int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();

//    concussion::Application app;
//    app.run();

    using namespace concussion;

    CNCEngine engine;

    EntityManager* manager = engine.getEntityManager();

    EntityID a = manager->create< Grenade >();
    EntityID b = manager->create< Grenade >();
    Grenade* ga = manager->get< Grenade >( a );
    Grenade* gb = manager->get< Grenade >( b );
    CNC_ASSERT( ga->getID() == a );
    CNC_ASSERT( gb->getID() == b );
    CNC_ASSERT( ga != nullptr );
    CNC_ASSERT( gb != nullptr );
    CNC_ERROR << "A : typeID=" << ga->getTypeID() << ", ID=" << ga->getID();
    CNC_ERROR << "B : typeID=" << gb->getTypeID() << ", ID=" << gb->getID();
    manager->destroy< Grenade >( a );
    manager->destroy< Grenade >( b );
    ga = manager->get< Grenade >( a );
    gb = manager->get< Grenade >( b );
    CNC_ASSERT( ga == nullptr );
    CNC_ASSERT( gb == nullptr );
    return 0;
}

