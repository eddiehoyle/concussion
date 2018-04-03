#ifndef CONCUSSION_MANAGER_HH
#define CONCUSSION_MANAGER_HH

#include <unordered_map>
#include <CEngine/Assert.hh>

namespace concussion {

class ComponentManager;

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

    template<class T, class... ARGS>
    EntityID create( ARGS&&... args ) {
        AbstractContainer* container = new EntityContainer< T >( T( std::forward<ARGS>(args)... ) );
        EntityID id = acquire( container );
        return id;
    }

    template< typename T >
    void destroy( EntityID id ) {
//        auto iter = m_entities.find( id );
//        CNC_ASSERT( iter != m_entities.end() );
//        delete m_entities[ id ];
//        m_entities.erase( iter );
    }

    template< typename T >
    T* get( EntityID id ) {
//        auto iter = m_entities.find( id );
//        CNC_ASSERT( iter != m_entities.end() );
//        return &static_cast< EntityContainer< T >* >( iter->second )->get();
        return nullptr;
    }
private:

    EntityID acquire( AbstractContainer* container ) {
        EntityID id = container->type();
        return id;
    }

private:
    std::unordered_map< unsigned int, AbstractContainer* > m_entities;
};

} // namespace concussion

#endif //CONCUSSION_MANAGER_HH
