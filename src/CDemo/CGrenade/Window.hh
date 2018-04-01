#ifndef CONCUSSION_WINDOW_HH
#define CONCUSSION_WINDOW_HH

#include <string>
#include <functional>
#include <map>
#include <vector>

#include <glm/glm.hpp>

class GLFWwindow;

namespace concussion {

class Window;
class Update;

glm::vec3 compute_world_ray( const glm::vec2& window,
                             const glm::vec2& mouse,
                             const glm::mat4& view,
                             const glm::mat4& projection );

class Window {
public:
    Window();
    ~Window();
    void set_title( const std::string& title );
    bool open() const;
    void update_begin( Update* update );
    void update_end();
    double time() const;
    void request_quit();

    unsigned int width() const;
    unsigned int height() const;
    glm::uvec2 viewport() const;

private:
    bool m_initialised;
    GLFWwindow *m_handle;

public:

    using Callback = std::function< void() >;

    void add_binding( int key, const Callback& callback ) {
        m_Callbacks[key].push_back( callback );
    }

    void onKeyPress( int key ) {
        for ( Callback& callback : m_Callbacks[key] ) {
            callback();
        }
    }

private:
    std::map< int, std::vector< Callback > > m_Callbacks;

};

}

#endif //CONCUSSION_WINDOW_HH
