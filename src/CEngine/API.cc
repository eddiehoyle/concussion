#include "API.hh"
#include "Engine.hh"

namespace concussion {

CNCEngine *CNC_Engine = nullptr;

void initialize() {
    CNC_ERROR << "initializing engine...";
    if ( CNC_Engine == nullptr ) {
        CNC_Engine = new CNCEngine();
    }
}

void terminate() {
    CNC_ERROR << "shutting down engine...";
    if ( CNC_Engine != nullptr ) {
        delete CNC_Engine;
        CNC_Engine = nullptr;
    }
}

}