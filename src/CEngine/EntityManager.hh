#ifndef CONCUSSION_MANAGER_HH
#define CONCUSSION_MANAGER_HH

#include <unordered_map>
#include <CEngine/Assert.hh>

namespace concussion {

class ComponentManager;

class EntityManager {

    class IContainer {
        friend class EntityManager;
    public:
        unsigned int id() const { return m_id; }
    private:
        unsigned int m_id;
    };

    template<class T >
    class EntityContainer : public IContainer {
    public:
        EntityContainer( T type ) : m_type( type ) {}
        T& get() { return m_type; }
    private:
        T m_type;
    };

public:

    EntityManager() = default;
    ~EntityManager() = default;

    template<class T, class... ARGS>
    unsigned int create( ARGS&&... args ) {
        unsigned int id = m_entities.size();
        IContainer* container = new EntityContainer< T >( T( std::forward<ARGS>(args)... ) );
        container->m_id = id;
        m_entities[id] = container;
        return id;
    }

    template< typename T >
    void destroy( unsigned int id ) {
        auto iter = m_entities.find( id );
        CNC_ASSERT( iter != m_entities.end() );
        delete m_entities[ id ];
        m_entities.erase( iter );
    }

    template< typename T >
    T* get( unsigned int id ) {
        auto iter = m_entities.find( id );
        CNC_ASSERT( iter != m_entities.end() );
        return &static_cast< EntityContainer< T >* >( iter->second )->get();
    }


private:
    std::unordered_map< unsigned int, IContainer* > m_entities;
};

} // namespace concussion

#endif //CONCUSSION_MANAGER_HH
