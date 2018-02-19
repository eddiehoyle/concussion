//
// Created by Eddie Hoyle on 19/02/18.
//

#ifndef CONCUSSION_WINDOW_HH
#define CONCUSSION_WINDOW_HH

#include <GLFW/glfw3.h>

namespace concussion {

class Window {
public:
    Window();
    ~Window();

    bool is_open();

    void update_begin();
    void update( double elapsed );
    void update_end();


private:

    GLFWwindow* m_handle;

    unsigned int m_frames;
};

Window& window();

}

#define CNC_INITIALISE_WINDOW() ::concussion::window();




#endif //CONCUSSION_WINDOW_HH
