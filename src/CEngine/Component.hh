#ifndef CONCUSSION_COMPONENT_HH
#define CONCUSSION_COMPONENT_HH

#include "AbstractComponent.hh"
#include "ObjectType.hh"
#include "Platform.hh"
#include "Types.hh"

namespace concussion {

template< typename C >
class Component : public AbstractComponent {

public:
    static const ComponentTypeID COMPONENT_TYPE_ID;

public:

    Component() = default;
    virtual ~Component() = default;

    inline virtual const ComponentTypeID getTypeID() const override {
        return this->COMPONENT_TYPE_ID;
    }
};

template< typename C >
const concussion::ComponentTypeID concussion::Component<C>::COMPONENT_TYPE_ID = concussion::internal::ObjectTypeID<concussion::AbstractComponent>::get<C>();

} // namespace concussion


#endif //CONCUSSION_COMPONENT_HH
