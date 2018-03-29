#ifndef CONCUSSION_MANAGER_HH
#define CONCUSSION_MANAGER_HH

#include <utility>
#include <CBase/assert.hh>
#include <unordered_map>

namespace concussion {


class ComponentManager {

    class IContainer {};

    template<class T >
    class ComponentyContainer : public IContainer {
    public:
        ComponentyContainer( T type ) : m_type( type ) {}
        T& get() { return m_type; }
    private:
        T m_type;
    };

public:

    ComponentManager() = default;
    ~ComponentManager() = default;

    template<class T, class... ARGS>
    unsigned int create( ARGS&&... args ) {
        unsigned int id = m_components.size();
        IContainer* entity = new ComponentyContainer< T >( T( std::forward<ARGS>(args)... ) );
        m_components[id] = entity;
        return id;
    }

    template< typename T >
    void destroy( unsigned int id ) {
        auto iter = m_components.find( id );
        CNC_ASSERT( iter != m_components.end() );
        delete m_components[ id ];
        m_components.erase( iter );
    }

    template< typename T >
    T* get( unsigned int id ) {
        auto iter = m_components.find( id );
        CNC_ASSERT( iter != m_components.end() );
        return &static_cast< ComponentyContainer< T >* >( iter->second )->get();
    }

private:
    using ComponentMap = std::unordered_map< unsigned int, IContainer* >;
    using EntityComponentMap = std::unordered_map< unsigned int, IContainer* >;
    ComponentMap m_components;
    EntityComponentMap m_entityComponents;
};

} // namespace concussion

#endif // CONCUSSION_MANAGER_HH
