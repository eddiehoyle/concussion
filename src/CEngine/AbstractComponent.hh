#ifndef CONCUSSION_ABSTRACTCOMPONENT_HH
#define CONCUSSION_ABSTRACTCOMPONENT_HH

#include "Platform.hh"
#include "AbstractEntity.hh"

namespace concussion {

using ComponentId		= ObjectID;
using ComponentTypeId	= TypeID;

class IComponent {

    friend class ComponentManager;

protected:
    unsigned int m_hash;
    unsigned int m_id;
    unsigned int m_owner;

public:
    IComponent() = default;
    virtual ~IComponent() = default;

    unsigned int id() const { return this->m_id; }
    unsigned int owner() const { return this->m_owner; }
};

} // namespace component

#endif // CONCUSSION_ABSTRACTCOMPONENT_HH
