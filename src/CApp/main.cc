#include <iostream>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <GLFW/glfw3.h>

int main( int argc, const char* argv[] ) {
    glm::vec3 vec;
    if ( !glfwInit() ) {
        std::cerr << "glfw failed to init" << std::endl;
    }
    std::cerr << "hi" << std::endl;
    return 0;
}