#ifndef CONCUSSION_GRENADE_HH
#define CONCUSSION_GRENADE_HH

#include <CEngine/Entity.hh>
#include <CEngine/TransformComponent.hh>
#include <CEngine/event/AbstractEventListener.hh>
#include "Events.hh"

namespace concussion {

class Grenade : public Entity<Grenade>, public event::AbstractEventListener {
public:
    Grenade();
    virtual ~Grenade() = default;

private:

    void onKeyDownEvent(const KeyDownEvent* event) {
        CNC_ERROR << "Received KeyDownEvent!!";
    }
    void onKeyUpEvent(const KeyUpEvent* event) {
        CNC_ERROR << "Received KeyUpEvent!!";
    }

private:
    TransformComponent* m_transform;
};

}

#endif // CONCUSSION_GRENADE_HH
