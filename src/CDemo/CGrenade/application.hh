#ifndef CONCUSSION_APPLICATION_HH
#define CONCUSSION_APPLICATION_HH

namespace concussion {

class Application {

public:
    Application();
    ~Application();
    void run();
private:
    void update( double elapsed );

};

}

#endif //CONCUSSION_APPLICATION_HH
