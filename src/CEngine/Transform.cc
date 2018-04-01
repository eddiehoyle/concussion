#include "Transform.hh"
#include <glm/ext.hpp>

namespace concussion {

Transform::Transform()
        : m_transform( 1.0f ) {
}

Transform::Transform( const glm::mat4& matrix ) :
        m_transform( matrix ) {
}

Transform::Transform( const glm::vec3& position ) {
    m_transform = glm::translate( glm::mat4( 1.0f ), position );
}

Transform::Transform( const glm::vec2& position_xy ) {
    m_transform = glm::translate( glm::mat4( 1.0f ), glm::vec3( position_xy, 0.0f ) );
}

Transform::Transform( const glm::vec3& position, const glm::quat& rotation ) {
    glm::mat4 P = glm::translate( glm::mat4( 1.0f ), position );
    glm::mat4 R = glm::toMat4( rotation );
    m_transform = P * R;
}

Transform::Transform( const glm::vec3& position, const glm::vec3& axis, const float angle_radians ) {
    glm::mat4 P = glm::translate( glm::mat4( 1.0f ), position );
    glm::mat4 PR = glm::rotate( P, angle_radians, axis );
    m_transform = PR;
}

Transform::Transform( const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale ) {
    glm::mat4 P = glm::translate( glm::mat4( 1.0f ), position );
    glm::mat4 R = glm::toMat4( rotation );
    glm::mat4 PR = P * R;
    glm::mat4 PRS = glm::scale( PR, scale );

    m_transform = PRS;
}

Transform::Transform( const glm::vec3& position,
                      const glm::vec3& axis,
                      const float angle_radians,
                      const glm::vec3& scale ) {
    glm::mat4 P = glm::translate( glm::mat4( 1.0f ), position );
    glm::mat4 PR = glm::rotate( P, angle_radians, axis );
    glm::mat4 PRS = glm::scale( PR, scale );

    m_transform = PRS;
}

void Transform::setPosition( const glm::vec3& position ) {
    m_transform[3] = glm::vec4( position, m_transform[3].w );
}

void Transform::setRotation( const glm::vec3& rotation_euler_radians ) {
    const glm::vec3 Tr = getPosition();
    const glm::vec3 Sc = getScale();

    const glm::mat4 T = glm::translate( glm::mat4( 1.0f ), Tr );
    const glm::mat4 R = glm::yawPitchRoll( rotation_euler_radians.x,
                                           rotation_euler_radians.y,
                                           rotation_euler_radians.z );

    m_transform = T * R * glm::scale( Sc );
}

void Transform::setScale( const glm::vec3& scale ) {
    glm::vec3 Tr = getPosition();
    glm::vec3 Or = getRotation();

    auto T = glm::translate( glm::mat4( 1.0f ), Tr );
    auto R = glm::yawPitchRoll( Or.x, Or.y, Or.z );

    m_transform = T * R * glm::scale( scale );
}

void Transform::setRight( const glm::vec3& right ) {
    m_transform[0] = glm::vec4( right, m_transform[0].w );
}

void Transform::setUp( const glm::vec3& up ) {
    m_transform[1] = glm::vec4( up, m_transform[1].w );
}

void Transform::setForward( const glm::vec3& forward ) {
    m_transform[2] = glm::vec4( forward, m_transform[2].w );
}

glm::vec3 Transform::getRotation() const {
    glm::vec3 euler_angles;
    glm::extractEulerAngleXYZ( *const_cast< glm::mat4* >( &m_transform ),
                               euler_angles[0],
                               euler_angles[1],
                               euler_angles[2] );
    return euler_angles;
}

glm::vec3 Transform::getScale() const {
    glm::vec3 row[3];
    for ( size_t i = 0; i < 3; ++i )
        for ( int j = 0; j < 3; ++j )
            row[i][j] = m_transform[i][j];
    return glm::vec3( glm::length( row[0] ), glm::length( row[1] ), glm::length( row[1] ) );
}

} // namespace concussion