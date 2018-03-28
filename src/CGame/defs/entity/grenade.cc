#include "entity/grenade.hh"
#include <CBase/assert.hh>

namespace concussion {

namespace entity {

Grenade::Grenade()
        : m_matrix( 1 ),
//          m_shape( nullptr ),
          m_primed( false ),
          m_exploding( false ) {
}

//graphics::ShapePtr Grenade::get_shape() const {
//    return m_shape;
//}

const glm::mat4& Grenade::get_matrix() const {
    return m_matrix;
}

void Grenade::prime() {
    CNC_ASSERT( !m_released )
    m_primed = true;
}

void Grenade::release( float angle ) {
    CNC_ASSERT( m_primed );
    CNC_ASSERT( !m_released  )
    m_angle = angle;
}


void Grenade::update( double elapsed ) {
    CNC_ASSERT( m_primed );
}

bool Grenade::is_primed() const {
    return m_primed;
}

bool Grenade::is_released() const {
    return m_released;
}

bool Grenade::is_exploding() const {
    return m_exploding;
}

} // namespace entity

} // namespace concussion
