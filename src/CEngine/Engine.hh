#ifndef CONCUSSION_ENGINE_HH
#define CONCUSSION_ENGINE_HH

namespace concussion {

class Timer;
class EntityManager;
class SystemManager;
class ComponentManager;

class CNCEngine {

    friend class AbstractEntity;
    friend class AbstractComponent;
    friend class AbstractSystem;
    friend class EntityManager;
    friend class ComponentManager;

private:

    Timer* m_engineTime;
    EntityManager* m_entityManager;
    ComponentManager* m_componentManager;
    SystemManager* m_systemManager;

    CNCEngine( const CNCEngine& ) = delete;
    CNCEngine& operator=( CNCEngine& ) = delete;

public:

    CNCEngine();
    ~CNCEngine();

    EntityManager* getEntityManager();
    ComponentManager* getComponentManager();
    SystemManager* getSystemManager();
    void update( float tick_ms );
};

}

#endif //CONCUSSION_ENGINE_HH
