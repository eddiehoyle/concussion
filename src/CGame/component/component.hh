#ifndef CONCUSSION_COMPONENT_HH
#define CONCUSSION_COMPONENT_HH

namespace concussion {

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
//    static const ComponentTypeId STATIC_COMPONENT_TYPE_ID;

    Component() = default;
    virtual ~Component() = default;
};

} // namespace concussion

#endif //CONCUSSION_COMPONENT_HH
