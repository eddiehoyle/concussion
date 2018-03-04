#ifndef CONCUSSION_MOUSE_HH
#define CONCUSSION_MOUSE_HH

#include <memory>
#include <glm/glm.hpp>

class GLFWwindow;

namespace concussion {

class Mouse;

typedef std::shared_ptr< Mouse > MousePtr;

class Mouse {

public:
    Mouse();

    void reset( const glm::vec2& position );
    void update( const glm::vec2& position );
    void update( int x, int y );
    const glm::vec2& get_position() const;
    glm::vec2 get_delta() const;

private:
    glm::vec2 m_origin;
    glm::vec2 m_position;
    glm::vec2 m_previous;
};

} // namespace concussion

#endif //CONCUSSION_MOUSE_HH
