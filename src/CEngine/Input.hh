#ifndef CONCUSSION_INPUT_HH
#define CONCUSSION_INPUT_HH

#include <glm/glm.hpp>

namespace concussion {

struct Update {
    glm::vec2 position;
    bool pressed;
    double time;
};

}

#endif // CONCUSSION_INPUT_HH
