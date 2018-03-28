#ifndef CONCUSSION_GRENADE_HH
#define CONCUSSION_GRENADE_HH

#include <CGraphics/shape.hh>
#include <glm/glm.hpp>

namespace concussion {

namespace graphics {
struct Shape;
}

namespace entity {

class Grenade {

public:
    Grenade();
    ~Grenade() = default;

//    graphics::ShapePtr get_shape() const;
    const glm::mat4& get_matrix() const;
    void prime();
    void release( float angle );
    void update( double elapsed );
    bool is_primed() const;
    bool is_released() const;
    bool is_exploding() const;

private:
//    graphics::ShapePtr m_shape;
    glm::mat4 m_matrix;
    float m_angle;

    bool m_primed;
    bool m_released;
    bool m_exploding;
};

} // namespace entity

} // namespace concussion

#endif // CONCUSSION_GRENADE_HH
