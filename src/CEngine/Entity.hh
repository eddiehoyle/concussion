#ifndef CONCUSSION_ENTITY_HH
#define CONCUSSION_ENTITY_HH

#include "AbstractEntity.hh"
#include "Assert.hh"
#include "Platform.hh"
#include "ObjectType.hh"
#include "Log.hh"

namespace concussion {

template< typename E >
class Entity : public AbstractEntity {

public:

    static const EntityTypeID ENTITY_TYPE_ID;

public:

    virtual const EntityTypeID getTypeID() const override {
        return this->ENTITY_TYPE_ID;
    }

    Entity() = default;
    virtual ~Entity() = default;
};

template< typename E >
const concussion::EntityTypeID Entity<E>::ENTITY_TYPE_ID =
        concussion::internal::ObjectTypeID<concussion::AbstractEntity>::get<E>();
} // namespace concussion

#endif // CONCUSSION_ENTITY_HH
