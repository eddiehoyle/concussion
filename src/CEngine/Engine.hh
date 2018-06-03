#ifndef CONCUSSION_ENGINE_HH
#define CONCUSSION_ENGINE_HH

#include <CEngine/event/EventHandler.hh>

namespace concussion {

class Timer;
class EntityManager;
class SystemManager;
class ComponentManager;

namespace event {

class AbstractEvent;
class AbstractEventListener;
class EventHandler;

}

class CNCEngine {

    friend class AbstractEntity;
    friend class AbstractComponent;
    friend class AbstractSystem;
    friend class event::AbstractEvent;
    friend class event::AbstractEventListener;

    friend class EntityManager;
    friend class ComponentManager;

private:

    Timer* CNC_EngineTime;
    EntityManager *CNC_EntityManager;
    ComponentManager *CNC_ComponentManager;
    SystemManager *CNC_SystemManager;
    event::EventHandler *CNC_EventHandler;

    CNCEngine( const CNCEngine& ) = delete;

    CNCEngine& operator=( CNCEngine& ) = delete;

public:

    CNCEngine();
    ~CNCEngine();

    void update( float tick_ms );

    template< class E, class... ARGS >
    void sendEvent( ARGS&& ... eventArgs ) {
        CNC_EventHandler->send< E >( std::forward< ARGS >( eventArgs )... );
    }

private:

    template< class E >
    inline void subscribeEvent( event::AbstractEventDelegate *eventDelegate ) {
        CNC_EventHandler->addEventCallback< E >( eventDelegate );
    }
};

}

#endif //CONCUSSION_ENGINE_HH
