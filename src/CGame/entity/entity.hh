#ifndef CONCUSSION_ENTITY_HH
#define CONCUSSION_ENTITY_HH

#include <unordered_map>
#include <CBase/assert.hh>

namespace concussion {

class ComponentManager;

class IEntity {

    friend class EntityManager;

private:

    // set on create; in EntityManager
    ComponentManager*	m_componentManager;

protected:

    int m_id;

public:

    IEntity();
    virtual ~IEntity();


    template<class T>
    T* getComponent() const {
        return this->m_componentManager->getComponent<T>(this->m_id);
    }

    template<class T, class ...P>
    T* AddComponent(P&&... param) {
        return this->m_componentManager->addComponent<T>(this->m_id, std::forward<P>(param)...);
    }

    template<class T>
    void RemoveComponent() {
        this->m_componentManager->removeComponent<T>(this->m_id);
    }
};

} // namespace concussion

#endif //CONCUSSION_MANAGER_HH
