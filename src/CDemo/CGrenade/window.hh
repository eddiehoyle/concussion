#ifndef CONCUSSION_WINDOW_HH
#define CONCUSSION_WINDOW_HH

#include <string>

class GLFWwindow;

namespace concussion {

class Window {
public:
    Window();
    ~Window();
    void set_title( const std::string& title );
    bool open();
    void update_begin();
    void update_end();
    double time() const;

private:
    bool m_initialised;
    GLFWwindow* m_handle;
};

}

#endif //CONCUSSION_WINDOW_HH
