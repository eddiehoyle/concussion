#ifndef CONCUSSION_MANAGER_HH
#define CONCUSSION_MANAGER_HH

#include <utility>
#include <CBase/assert.hh>
#include <unordered_map>
#include <vector>

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
    unsigned int add( unsigned int entity_id, unsigned int component_id, ARGS&&... args ) {
        IContainer* component = new ComponentyContainer< T >( T( std::forward<ARGS>(args)... ) );
        if ( m_components.find( entity_id ) == m_components.end() ) {
            m_components[ entity_id ] = ComponentMap();
        }
        m_components[entity_id][component_id] = component;
        return component_id;
    }

    template< typename T >
    void remove( unsigned int entity_id, unsigned int component_id ) {
        auto entity_iter = m_components.find( entity_id );
        CNC_ASSERT( entity_iter != m_components.end() );
        auto component_iter = entity_iter->second.find( component_id );
        CNC_ASSERT( component_iter != entity_iter->second.end() );
        delete component_iter->second;
        entity_iter->second.erase( component_iter );
        if ( entity_iter->second.empty() ) {
            m_components.erase( entity_iter );
        }
    }

    template< typename T >
    T* get( unsigned int entity_id, unsigned int component_id ) {
        auto entity_iter = m_components.find( entity_id );
        CNC_ASSERT( entity_iter != m_components.end() );
        auto component_iter = entity_iter->second.find( component_id );
        CNC_ASSERT( component_iter != entity_iter->second.end() );
        return &static_cast< ComponentyContainer< T >* >( component_iter->second )->get();
    }

private:
    using ComponentMap = std::unordered_map< unsigned int, IContainer* >;
    using EntityComponentMap = std::unordered_map< unsigned int, ComponentMap >;
    EntityComponentMap m_components;
};

} // namespace concussion

#endif // CONCUSSION_MANAGER_HH
