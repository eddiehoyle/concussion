#ifndef CONCUSSION_COMPONENTTRANSFORM_HH
#define CONCUSSION_COMPONENTTRANSFORM_HH

#include "Transform.hh"
#include "Component.hh"

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

    glm::mat4 m_transform;

}; // class TransformComponent

}


#endif //CONCUSSION_COMPONENTTRANSFORM_HH
