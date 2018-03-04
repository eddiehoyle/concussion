#ifndef CONCUSSION_WINDOW_HH
#define CONCUSSION_WINDOW_HH

#include <string>
#include <functional>
#include <map>
#include <vector>

class GLFWwindow;

namespace concussion {

class Window {
public:
    Window();

    ~Window();

    void set_title( const std::string& title );

    bool open() const;

    void update_begin();

    void update_end();

    double time() const;

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
