#ifndef CONCUSSION_COMPONENT_HH
#define CONCUSSION_COMPONENT_HH

#include "AbstractComponent.hh"
#include "ObjectType.hh"
#include "Platform.hh"

namespace concussion {
template< class T >
class Component : public AbstractComponent {

public:

    static const ComponentTypeId COMPONENT_TYPE_ID;

public:

    Component()
    {}

    virtual ~Component()
    {}
};

//template<class T>
//const ComponentTypeId Component<T>::COMPONENT_TYPE_ID = internal::ObjectTypeID<AbstractComponent>::get<T>();

} // namespace concussion

#endif //CONCUSSION_COMPONENT_HH
