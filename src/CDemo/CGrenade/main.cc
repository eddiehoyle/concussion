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


struct SomeEvent : public concussion::event::Event<SomeEvent>
{};



int main( int argc, const char* argv[] ) {

    CNC_INITIALISE_LOG();

    concussion::event::EventHandler handler;
    handler.send<SomeEvent>();
    handler.dispatch();


//    concussion::Application app;
//    app.run();

    using namespace concussion;


    return 0;
}

