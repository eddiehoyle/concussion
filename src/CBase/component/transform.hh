#ifndef CONCUSSION_TRANSFORM_HH
#define CONCUSSION_TRANSFORM_HH

#include "component.hh"
#include <CBase/transform.hh>

#include <glm/glm.hpp>

namespace concussion {

class TransformComponent : public Component< TransformComponent > {

public:

    TransformComponent() = default;
    explicit TransformComponent( const glm::mat4& transform );
//    explicit TransformComponent(const Transform& transform);

    virtual ~TransformComponent() = default;

//    inline void SetTransform(const glm::mat4& transform) { this->m_Transform = transform; }
//
//    inline Transform* AsTransform() { return &(this->m_Transform); }
//
//    inline const float*		AsFloat() const { return this->m_Transform; }
//    inline const glm::mat4& AsMat4() const { return this->m_Transform; }

private:

//    Transform	m_Transform;

}; // class TransformComponent

}


#endif //CONCUSSION_TRANSFORM_HH
