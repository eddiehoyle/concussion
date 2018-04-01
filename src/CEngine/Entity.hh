#ifndef CONCUSSION_ENTITY_HH
#define CONCUSSION_ENTITY_HH

#include "AbstractEntity.hh"

#include "Assert.hh"
#include "Component.hh"
#include "ComponentManager.hh"
#include "Platform.hh"

namespace concussion {

template<class E>
class Entity : public AbstractEntity {

    // Entity destruction always happens through EntityManager !!!
    void operator delete(void*) = delete;
    void operator delete[](void*) = delete;

public:

    static const EntityTypeId STATIC_ENTITY_TYPE_ID;

public:

    virtual const EntityTypeId getTypeID() const override {
        return STATIC_ENTITY_TYPE_ID;
    }

    Entity()
    {}

    virtual ~Entity()
    {}
};

// set unique type id for this Entity<T>
template<class E>
const EntityTypeId Entity<E>::STATIC_ENTITY_TYPE_ID = internal::FamilyTypeID<AbstractEntity>::get<E>();

} // namespace concussion

#endif //CONCUSSION_ENTITY_HH
