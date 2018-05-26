#ifndef CONCUSSION_ABSTRACTCOMPONENT_HH
#define CONCUSSION_ABSTRACTCOMPONENT_HH

#include "Platform.hh"
#include "Types.hh"

namespace concussion {

class AbstractComponent {

    friend class ComponentManager;

protected:
    ComponentID  m_ID;
    EntityID m_entityID;

public:
    AbstractComponent() = default;
    virtual ~AbstractComponent() = default;

    inline const ComponentID getID() const { return this->m_ID; }
    inline virtual const ComponentTypeID getTypeID() const = 0;
    inline const EntityID getEntityID() const { return this->m_entityID; }
};

} // namespace component

#endif // CONCUSSION_ABSTRACTCOMPONENT_HH
