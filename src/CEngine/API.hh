#ifndef CONCUSSION_API_HH
#define CONCUSSION_API_HH

#include "Engine.hh"

namespace concussion {

class CNCEngine;

extern CNCEngine *CNC_Engine;

void initialize();
void terminate();

}


#endif //CONCUSSION_API_HH
