#ifndef CONCUSSION_ENTITYMANAGER_HH
#define CONCUSSION_ENTITYMANAGER_HH

#include "Assert.hh"
#include "Entity.hh"
#include "ComponentManager.hh"

#include <memory>
#include <unordered_map>

namespace concussion {

class EntityManager {

    class AbstractContainer {
        friend class EntityManager;
    public:
        EntityID id() const { return m_id; }
        EntityTypeID type() const { return m_type; }
    protected:
        EntityID m_id;
        EntityTypeID m_type;
    };

    template<class T >
    class EntityContainer : public AbstractContainer {
    public:
        EntityContainer( T entity )
                : m_entity( entity ) {
            m_type = T::ENTITY_TYPE_ID;
        }
        T& get() { return m_entity; }
    private:
        T m_entity;
    };

public:

    EntityManager() = default;
    ~EntityManager() = default;

    /// Create an entity.
    /// @tparam T Type of entity.
    /// @tparam Args Entity arguments type.
    /// @param args Entity arguments
    /// @return An entity id.
    template<class T, class... Args>
    EntityID create( Args&&... args ) {
        EntityContainer< T >* container = new EntityContainer< T >( T( std::forward<Args>(args)... ) );
        EntityID id = acquire( container );
        container->get().m_componentManager = m_componentManager;
        container->get().m_ID = id;
        CNC_ERROR << "Created entity: " << (void*)&container->get();
        return id;
    }

    /// Destroy an entity.
    /// @tparam T Type of entity.
    /// @param id Id of entity.
    template< typename T >
    void destroy( EntityID id ) {
        CNC_ASSERT( id < m_containers.size() );
        EntityContainer< T >* container = get_container< T >( id );
        CNC_ASSERT( container != nullptr );
        CNC_ERROR << "Deleting entity: " << (void*)&container->get();

        auto type_iter = m_entities.find( container->type() );
        CNC_ASSERT( type_iter != m_entities.end() );
        auto id_iter = std::find( type_iter->second.begin(), type_iter->second.end(), container->id() );
        CNC_ASSERT( id_iter != type_iter->second.end() );
        type_iter->second.erase( id_iter );

        delete m_containers[ id ];
        m_containers[ id ] = nullptr;
    }

    /// Get an entity.
    /// @tparam T The type of entity.
    /// @param id The id of the entity.
    /// @return A pointer to the entity for id.
    template< typename T >
    T* get( EntityID id ) {
        CNC_ASSERT( id < m_containers.size() );
        EntityContainer< T >* container = get_container< T >( id );
        return container != nullptr ? &container->get() : nullptr;
    }

private:

    /// Acquire an entity id and store the container.
    /// @param container An entities container.
    /// @return The entity id for this container.
    EntityID acquire( AbstractContainer* container ) {

        EntityID entity_id = 0;

        auto container_iter = std::find( m_containers.begin(), m_containers.end(), nullptr );
        if ( container_iter != m_containers.end() ) {
            entity_id = static_cast< EntityID >( std::distance( m_containers.begin(), container_iter ) );
        } else {
            entity_id = m_containers.size();
            m_containers.resize( m_containers.size() + 1 ); // check size here
        }

        container->m_id = entity_id;

        auto type_iter = m_entities.find( container->type() );
        if ( type_iter == m_entities.end() ) {
            m_entities[ container->type() ] = std::vector< EntityID >();
        }

        m_entities[ container->type() ].push_back( entity_id );
        m_containers[ container->id() ] = container;

        return entity_id;
    }

    /// Get the container for entity id.
    /// @tparam T The type of entity.
    /// @param id The id of the entity.
    /// @return The entity container.
    template< typename T >
    EntityContainer< T >* get_container( EntityID id ) {
        return static_cast< EntityContainer< T >* >( m_containers[ id ] );
    }

private:

    using EntityIDs = std::vector< EntityID >;
    using EntityIDMap = std::unordered_map< EntityTypeID, EntityIDs >;
    using Containers = std::vector< AbstractContainer* >;

    EntityIDMap m_entities;
    Containers m_containers;

    ComponentManager* m_componentManager;

};

} // namespace concussion

#endif // CONCUSSION_ENTITYMANAGER_HH
