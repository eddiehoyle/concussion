#include "Grenade.hh"
#include "Backpack.hh"
#include "Application.hh"

#include <CEngine/Log.hh>
#include <CEngine/Assert.hh>
#include <CEngine/Engine.hh>
#include <CEngine/EntityManager.hh>
#include <CEngine/event/Event.hh>
#include <CEngine/event/AbstractEvent.hh>
#include <CEngine/event/AbstractEventListener.hh>

#include <memory>
#include <CEngine/event/EventHandler.hh>
#include "Events.hh"
#include <CEngine/API.hh>


int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();


    using namespace concussion;

    initialize();

    Grenade grenade;

    CNC_Engine->sendEvent<KeyDownEvent>( 5 );
    CNC_Engine->sendEvent<KeyUpEvent>( 3 );
    CNC_Engine->sendEvent<KeyDownEvent>( 7 );
    CNC_Engine->update( 1 );

    terminate();


//    concussion::Application app;
//    app.run();

    using namespace concussion;


    return 0;
}

