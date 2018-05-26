#ifndef CONCUSSION_GRENADE_HH
#define CONCUSSION_GRENADE_HH

#include <CEngine/Entity.hh>
#include <CEngine/TransformComponent.hh>

namespace concussion {

class Grenade : public Entity<Grenade> {
public:
    Grenade();
    virtual ~Grenade() {}
private:
    TransformComponent* m_transform;
};

}

#endif // CONCUSSION_GRENADE_HH
