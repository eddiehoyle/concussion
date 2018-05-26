#ifndef CONCUSSION_COMPONENTMANAGER_HH
#define CONCUSSION_COMPONENTMANAGER_HH

#include "Assert.hh"
#include "Platform.hh"
#include "AbstractComponent.hh"


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
    ComponentID add( EntityID entity_id, ARGS&&... args ) {
//        IContainer* component = new ComponentyContainer< T >( T( std::forward<ARGS>(args)... ) );
//        if ( m_components.find( entity_id ) == m_components.end() ) {
//            m_components[ entity_id ] = EntityComponentMap();
//        }
//        m_components[entity_id][T::component_id] = component;
        ComponentID component_id;
        return component_id;
    }

    template< typename T >
    void remove( EntityID id ) {
//        auto entity_iter = m_components.find( entity_id );
//        CNC_ASSERT( entity_iter != m_components.end() );
//        auto component_iter = entity_iter->second.find( component_id );
//        CNC_ASSERT( component_iter != entity_iter->second.end() );
//        delete component_iter->second;
//        entity_iter->second.erase( component_iter );
//        if ( entity_iter->second.empty() ) {
//            m_components.erase( entity_iter );
//        }
    }

    template< typename T >
    T* get( EntityID entity_id ) {
//        auto entity_iter = m_components.find( entity_id );
//        CNC_ASSERT( entity_iter != m_components.end() );
//        auto component_iter = entity_iter->second.find( component_id );
//        CNC_ASSERT( component_iter != entity_iter->second.end() );
//        return &static_cast< ComponentyContainer< T >* >( component_iter->second )->get();
        return nullptr;
    }

private:
//    using EntityComponentMap =  std::vector< std::vector< unsigned int > >;
    using EntityComponentMap =  std::map< EntityID, std::vector< ComponentID > >;
    EntityComponentMap m_components;
    std::vector< IContainer* > m_lut;
};

} // namespace concussion

#endif // CONCUSSION_COMPONENTMANAGER_HH
