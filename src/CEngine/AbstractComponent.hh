#ifndef CONCUSSION_ABSTRACTCOMPONENT_HH
#define CONCUSSION_ABSTRACTCOMPONENT_HH

#include "Platform.hh"
#include "AbstractEntity.hh"

namespace concussion {

using ComponentId		= ObjectID;
using ComponentTypeId	= TypeID;

class AbstractComponent {

    friend class ComponentManager;

protected:
    unsigned int m_hash;
    ComponentId  m_id;
    EntityID m_owner;

public:
    AbstractComponent() = default;
    virtual ~AbstractComponent() {}

    ComponentId id() const { return this->m_id; }
    EntityID owner() const { return this->m_owner; }
};

} // namespace component

#endif // CONCUSSION_ABSTRACTCOMPONENT_HH
