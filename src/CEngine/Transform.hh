#ifndef CONCUSSION_TRANSFORM_HH
#define CONCUSSION_TRANSFORM_HH

#include <glm/glm.hpp>

namespace concussion {

// From article:
// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/the-entity-component-system-c-game-design-pattern-part-1-r4803/

class Transform {

public:

    static Transform identity() { return Transform(); }

public:

    Transform();
    explicit Transform( const glm::mat4& matrix );
    explicit Transform( const glm::vec2& position_xy );
    explicit Transform( const glm::vec3& position );
    explicit Transform( const glm::vec3& position, const glm::quat& rotation );
    explicit Transform( const glm::vec3& position, const glm::vec3& axis, const float angle );
    explicit Transform( const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale );
    explicit Transform( const glm::vec3& position, const glm::vec3& axis, const float angle, const glm::vec3& scale );

    inline void zero() { this->m_transform = glm::mat4(0.0f); }
    inline void reset() { this->m_transform = glm::mat4(1.0f); }

    void setPosition( const glm::vec3& position );
    void setRotation( const glm::vec3& rotation_euler );
    void setScale( const glm::vec3& scale );

    inline glm::vec3 getRight() const { return glm::vec3(this->m_transform[0]); }
    inline glm::vec3 getUp() const { return glm::vec3(this->m_transform[1]); }
    inline glm::vec3 getForward() const { return glm::vec3(this->m_transform[2]); }
    inline glm::vec3 getPosition() const { return glm::vec3(this->m_transform[3]); }

    void setRight(const glm::vec3& right);
    void setUp(const glm::vec3& up);
    void setForward(const glm::vec3& forward);

    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

private:

    glm::mat4	m_transform;

};

} // namespace concussion

#endif //CONCUSSION_TRANSFORM_HH
