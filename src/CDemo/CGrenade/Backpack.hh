#ifndef CONCUSSION_BACKPACK_HH
#define CONCUSSION_BACKPACK_HH

#include <CEngine/Entity.hh>
#include <CEngine/TransformComponent.hh>

namespace concussion {

class Backpack : public Entity<Backpack> {
public:
    Backpack() {}
    virtual ~Backpack() {}
private:
    TransformComponent* m_transform;
};

}

#endif // CONCUSSION_BACKPACK_HH
