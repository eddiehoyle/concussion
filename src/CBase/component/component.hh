#ifndef CONCUSSION_COMPONENT_HH
#define CONCUSSION_COMPONENT_HH

#include <CBase/entity/abstract.hh>
#include <CBase/internal/family.hh>
#include <CBase/platform.hh>

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
