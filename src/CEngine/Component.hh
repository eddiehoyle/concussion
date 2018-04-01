#ifndef CONCUSSION_COMPONENT_HH
#define CONCUSSION_COMPONENT_HH

#include "AbstractComponent.hh"
#include "Family.hh"
#include "Platform.hh"

namespace concussion {
template< class T >
class Component : public IComponent {

public:

    // This is an id that should be counted somewhere as a unique identifier
    static const unsigned int STATIC_COMPONENT_TYPE_ID;

    Component() = default;
    virtual ~Component() = default;
};

// This private member only exists to force the compiler to create an instance of Component T,
// which will set its unique identifier.
template<class T>
const unsigned int Component<T>::STATIC_COMPONENT_TYPE_ID = internal::FamilyTypeID<IComponent>::get<T>();

} // namespace concussion

#endif //CONCUSSION_COMPONENT_HH
