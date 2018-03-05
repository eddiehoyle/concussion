#include "input/mouse.hh"
#include <GLFW/glfw3.h>
#include <CBase/log.hh>
#include <glm/ext.hpp>

namespace concussion {
//
//Mouse::Mouse()
//        : m_origin( 0, 0 ),
//          m_position( 0, 0 ),
//          m_previous( 0, 0 ) {
//    CNC_ERROR << "Starting mouse";
//}
//
//void Mouse::reset( const glm::vec2& origin ) {
//    m_origin = origin;
//    m_previous = origin;
//    m_position = origin;
//}
//
//void Mouse::update( const glm::vec2& position ) {
//    CNC_ERROR << "position=" << glm::to_string( m_position );
//    m_previous = m_position;
//    m_position = position;
//}
//
//void Mouse::update( int x, int y ) {
//    update( glm::vec2( x, y ) );
//}
//
//const glm::vec2& Mouse::get_position() const {
//    return m_position;
//}
//
//glm::vec2 Mouse::get_delta() const {
//    return m_previous - m_position ;
//}

}