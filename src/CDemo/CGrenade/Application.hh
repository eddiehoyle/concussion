#ifndef CONCUSSION_APPLICATION_HH
#define CONCUSSION_APPLICATION_HH

#include "Window.hh"

#include <memory>

namespace concussion {

class Application {

public:
    Application();
    ~Application() = default;
    void run();
private:
    std::unique_ptr< Window > m_window;
};

}

#endif //CONCUSSION_APPLICATION_HH
