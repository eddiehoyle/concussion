#ifndef CONCUSSION_ABSTRACTENTITY_HH
#define CONCUSSION_ABSTRACTENTITY_HH

#include "Assert.hh"
#include "Types.hh"
#include "ComponentManager.hh"

namespace concussion {

class AbstractEntity {

    friend class EntityManager;

public:

    AbstractEntity();
    virtual ~AbstractEntity() = default;

    inline const EntityID getID() const { return this->m_id; }
    inline virtual const EntityID getTypeID() const = 0;

    template<class T>
    T* getComponent() const {
        return this->m_componentManager->get<T>(this->m_id);
    }

    template<class T, class ...P>
    ComponentID addComponent(P&&... param) {
        return this->m_componentManager->add< T >( this->m_id, std::forward<P>(param)...);
    }

    template<class T>
    void removeComponent() {
        this->m_componentManager->remove<T>(this->m_id);
    }

protected:

    EntityID m_id;

    ComponentManager* m_componentManager;

};

} // namespace concussion

#endif // CONCUSSION_ABSTRACTENTITY_HH
