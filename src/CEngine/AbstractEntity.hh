#ifndef CONCUSSION_ABSTRACTENTITY_HH
#define CONCUSSION_ABSTRACTENTITY_HH

#include "Assert.hh"
#include "Platform.hh"

namespace concussion {

class ComponentManager;

using EntityID		= ObjectID;
using EntityTypeID	= TypeID;

class AbstractEntity {

    friend class EntityManager;

public:

    AbstractEntity() = default;
    virtual ~AbstractEntity() {}
    virtual const EntityTypeID getTypeID() const = 0;

    inline const EntityID getID() const {
        return this->m_id;
    }

    template<class T>
    T* getComponent() const {
//        return this->m_componentManager->get<T>(this->m_id);
        return nullptr;
    }

    template<class T, class ...P>
    T* addComponent(P&&... param) {
//        return this->m_componentManager->add<T>(this->m_id, std::forward<P>(param)...);
        return nullptr;
    }

    template<class T>
    void removeComponent() {
//        this->m_componentManager->remove<T>(this->m_id);
    }

private:

    ComponentManager* m_componentManager;

protected:

    EntityID m_id;
};

} // namespace concussion

#endif // CONCUSSION_ABSTRACTENTITY_HH
