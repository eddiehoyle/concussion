#ifndef CONCUSSION_CUBE_HH
#define CONCUSSION_CUBE_HH

#include "mesh.hh"

namespace concussion {

namespace graphics {

class Cube : public Mesh {
public:
    Cube();
    ~Cube() = default;
};

} // namespace graphics

} // namespace concussion

#endif //CONCUSSION_CUBE_HH
