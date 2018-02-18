#include <iostream>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <GLFW/glfw3.h>

#include <CBase/log.hh>

int main( int argc, const char* argv[] ) {
    glm::vec3 vec;
    if ( !glfwInit() ) {
        std::cerr << "glfw failed to init" << std::endl;
    }

    CNC_INITIALISE_LOG();

    CNC_DEBUG << "This is a debug message";
    CNC_INFO << "This is an info message";
    CNC_DEBUG << "This is a debug message";
    CNC_INFO << "This is an info message";

    CNC_ERROR << "This is an error message";
    CNC_WARN << "This is an warn message";
    CNC_ERROR << "This is an error message";
    CNC_WARN << "This is an warn message";

    return 0;
}
//
//#include <iostream>
//
//class Stream {
//public:
//    template< typename T >
//    Stream& operator<<( T value ) {
//        std::cerr << value;
//        return *this;
//    }
//};
//
//#define LOG Stream()
//
//int main( int argc, const char* argv[] ) {
//
//    LOG << "sdf";
//    return 0;
//}

