#ifndef CONCUSSION_ABSTRACT_HH
#define CONCUSSION_ABSTRACT_HH

#include <CBase/assert.hh>
#include <CBase/component/component.hh>
#include <CBase/platform.hh>

namespace concussion {

class ComponentManager;

using EntityId		= ObjectID;
using EntityTypeId	= TypeID;

class AbstractEntity {

    friend class EntityManager;

private:

    // set on create; in EntityManager
    ComponentManager* m_componentManager;

protected:

    EntityId m_id;

public:

    AbstractEntity() = default;
    virtual ~AbstractEntity() = default;

    virtual const EntityTypeId getTypeID() const = 0;

    inline const EntityId getID() const {
        return this->m_id;
    }

    template<class T>
    T* getComponent() const {
//        return this->m_componentManager->get<T>(this->m_id);
    }

    template<class T, class ...P>
    ComponentTypeId addComponent(P&&... param) {
//        return this->m_componentManager->add<T>(this->m_id, std::forward<P>(param)...);
    }

    template<class T>
    void removeComponent() {
//        this->m_componentManager->remove<T>(this->m_id);
    }
};

} // namespace concussion

#endif // CONCUSSION_ABSTRACT_HH
