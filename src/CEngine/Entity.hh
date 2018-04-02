#ifndef CONCUSSION_ENTITY_HH
#define CONCUSSION_ENTITY_HH

#include "AbstractEntity.hh"
#include "Assert.hh"
#include "Platform.hh"
#include "ObjectType.hh"

namespace concussion {

template<class E>
class Entity : public AbstractEntity {

public:

    static const EntityTypeID ENTITY_TYPE_ID;

public:

    virtual const EntityTypeID getTypeID() const override {
        return ENTITY_TYPE_ID;
    }

    Entity()
    {}

    virtual ~Entity()
    {}
};

//template<class E>
//const EntityTypeID Entity<E>::ENTITY_TYPE_ID = internal::ObjectTypeID<AbstractEntity>::get<E>();

} // namespace concussion

#endif // CONCUSSION_ENTITY_HH
