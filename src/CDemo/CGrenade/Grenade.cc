
#include <functional>

#include "Grenade.hh"
#include <CEngine/ComponentManager.hh>

namespace concussion {

Grenade::Grenade()
    : Entity< Grenade >(),
      m_transform( nullptr ) {
    m_transform = m_componentManager->get< TransformComponent >( this->getID() );
    registerEventCallback( &Grenade::onKeyDownEvent );
    registerEventCallback( &Grenade::onKeyUpEvent );
}





} // namespace concussion