#ifndef CONCUSSION_GAMEOBJECT_HH
#define CONCUSSION_GAMEOBJECT_HH

#include "Entity.hh"
#include "TransformComponent.hh"

namespace concussion {

template<class T>
class GameObject : public Entity<T> {
public:

    GameObject() {
        addComponent<TransformComponent>(Transform());
    }

    virtual ~GameObject() {
    }

};

}

#endif //CONCUSSION_GAMEOBJECT_HH
