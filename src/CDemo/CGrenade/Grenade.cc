#include "Grenade.hh"

namespace concussion {

Grenade::Grenade() {
    this->m_transform = getComponent<TransformComponent>();
}

Grenade::~Grenade() {
}

} // namespace concussion