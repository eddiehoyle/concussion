#ifndef CONCUSSION_ASSERT_HH
#define CONCUSSION_ASSERT_HH

//#include <cstdlib>
//#include <cstdio>

#include "log.hh"

#if CNC_ASSERT_ENABLED
#define STR(condition) #condition
#define CNC_ASSERT(condition) \
    if ( !condition ) {\
        CNC_ERROR << "Assertion failed: " << STR(condition);\
        abort();\
    }
#else
#define CNC_ASSERT(ignore) ((void)0)
#endif


#endif //CONCUSSION_ASSERT_HH
