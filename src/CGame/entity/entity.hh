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
    ComponentManager* m_componentManager;

protected:

    int m_id;

public:

    IEntity() = default;
    virtual ~IEntity() = default;

    template<class T>
    T* getComponent() const {
        return this->m_componentManager->get<T>(this->m_id);
    }

    template<class T, class ...P>
    T* addComponent(P&&... param) {
        return this->m_componentManager->add<T>(this->m_id, std::forward<P>(param)...);
    }

    template<class T>
    void removeComponent() {
        this->m_componentManager->remove<T>(this->m_id);
    }
};

} // namespace concussion

#endif //CONCUSSION_MANAGER_HH
