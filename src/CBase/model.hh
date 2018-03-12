#ifndef CONCUSSION_MODEL_HH
#define CONCUSSION_MODEL_HH

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <map>

namespace concussion {

/// TODO
struct Material {
    glm::vec3 ambient[3];
    glm::vec3 diffuse[3];
    glm::vec3 specular[3];
    glm::vec3 transmittance[3];
    glm::vec3 emission[3];
    float shininess;

    std::string ambient_name;
    std::string diffuse_texname;
    std::string specular_texname;
    std::string normal_texname;
    std::map< std::string, std::string > unknown_parameter;
};

/// TODO
struct Mesh {
    std::vector< float > vertices;
    std::vector< float > normals;
    std::vector< float > uvs;
    std::vector< unsigned int > indices;
};

/// TODO
struct Shape {
    Material material;
    Mesh mesh;
};

void load_obj( const std::string& path, Shape& shape );

} // namespace concussion

#endif //CONCUSSION_MODEL_HH
