#ifndef CONCUSSION_INTERSECT_HH
#define CONCUSSION_INTERSECT_HH

#include <glm/glm.hpp>

namespace concussion {

namespace graphics {

/// TODO
bool rayPlaneIntersect( const glm::vec3& plane_position,
                        const glm::vec3& plane_normal,
                        const glm::vec3& ray_origin,
                        const glm::vec3& ray_direction,
                        glm::vec3* intersection = nullptr );

} // namespace graphics

} // namespace concussion

#endif //CONCUSSION_INTERSECT_HH
