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

    Timer *m_engineTime;
    EntityManager *m_entityManager;
    ComponentManager *m_componentManager;
    SystemManager *m_systemManager;
    event::EventHandler *m_eventHandler;

    CNCEngine( const CNCEngine& ) = delete;

    CNCEngine& operator=( CNCEngine& ) = delete;

public:

    CNCEngine();

    ~CNCEngine();

    EntityManager *getEntityManager();

    ComponentManager *getComponentManager();

    SystemManager *getSystemManager();

    void update( float tick_ms );

    template< class E, class... ARGS >
    void sendEvent( ARGS&& ... eventArgs ) {
        m_eventHandler->send< E >( std::forward< ARGS >( eventArgs )... );
    }

private:

    template< class E >
    inline void subscribeEvent( event::AbstractEventDelegate *eventDelegate ) {
        m_eventHandler->addEventCallback< E >( eventDelegate );
    }
};

}

#endif //CONCUSSION_ENGINE_HH
