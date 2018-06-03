#include "Engine.hh"
#include "ComponentManager.hh"
#include "EntityManager.hh"
#include "Timer.hh"

namespace concussion {

CNCEngine::CNCEngine()
        : CNC_EngineTime( nullptr ),
          CNC_EntityManager( nullptr ),
          CNC_ComponentManager( nullptr ),
          CNC_SystemManager( nullptr ) {

    CNC_EngineTime = new Timer();
    CNC_EventHandler = new event::EventHandler();
    CNC_EntityManager = new EntityManager;
    CNC_ComponentManager = new ComponentManager;
}

CNCEngine::~CNCEngine() {
    delete CNC_EngineTime;
    delete CNC_EventHandler;
    delete CNC_EntityManager;
    delete CNC_ComponentManager;
}

void CNCEngine::update( float tick_ms ) {
    CNC_EventHandler->dispatch();
}

}
