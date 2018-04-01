#include "Intersect.hh"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

namespace concussion {

namespace graphics {

bool rayPlaneIntersect( const glm::vec3& plane_position,
                        const glm::vec3& plane_normal,
                        const glm::vec3& ray_origin,
                        const glm::vec3& ray_direction,
                        glm::vec3 *intersection ) {
    float denom = glm::dot( plane_normal, ray_direction );
    if ( fabs( denom ) > FLT_EPSILON ) {
        float distance = glm::dot( plane_position - ray_origin, plane_normal ) / denom;
        if ( intersection != nullptr ) {
            *intersection = ray_origin + ray_direction * distance;
        }
        return true;
    }
    return false;
}

}

}