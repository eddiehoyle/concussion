#include "Engine.hh"
#include "ComponentManager.hh"
#include "EntityManager.hh"

namespace concussion {

CNCEngine::CNCEngine()
    : m_entityManager( nullptr ),
      m_componentManager( nullptr ),
      m_systemManager( nullptr ) {

    m_eventHandler		= new event::EventHandler();

    m_componentManager = new ComponentManager;
    m_entityManager = new EntityManager;
}

CNCEngine::~CNCEngine() {
    delete m_entityManager;
    delete m_componentManager;
}

void CNCEngine::update( float tick_ms ) {
    m_eventHandler->dispatch();
}

EntityManager* CNCEngine::getEntityManager() {
    return m_entityManager;
}

ComponentManager* CNCEngine::getComponentManager() {
    return m_componentManager;
}

SystemManager* CNCEngine::getSystemManager() {
    return m_systemManager;
}


}
