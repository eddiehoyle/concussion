#ifndef CONCUSSION_MANAGER_HH
#define CONCUSSION_MANAGER_HH

#include <unordered_map>
#include <CBase/assert.hh>

namespace concussion {

/*
 *
 */

class ComponentManager;

class EntityManager {

    class IEntity {
    };

    template<class T >
    class EntityContainer : public IEntity {
    public:
        EntityContainer( T type ) : m_type( type ) {}
    private:
        T m_type;
    };

public:

    EntityManager() = default;
    ~EntityManager() = default;

    template<class T, class... ARGS>
    unsigned int create( ARGS&&... args ) {
        unsigned int id = m_entities.size();
        IEntity* entity = new EntityContainer< T >( T( std::forward<ARGS>(args)... ) );
        m_entities[id] = entity;
        return id;
    }

    void destroy( unsigned int id ) {
        CNC_ASSERT( m_entities.find( id ) != m_entities.end() );
        delete m_entities[ id ];
    }


private:
    std::unordered_map< unsigned int, IEntity* > m_entities;
};

} // namespace concussion

#endif //CONCUSSION_MANAGER_HH
