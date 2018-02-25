#ifndef CONCUSSION_ASSERT_HH
#define CONCUSSION_ASSERT_HH

#include "log.hh"

#if CNC_ASSERT_ENABLED
#define STR(exp) #exp
#define CNC_ASSERT(exp)                                         \
do {                                                            \
    if ( !( exp ) ) {                                           \
        CNC_ERROR << "Assertion failed: (" << STR(exp) << ") "  \
                  << "[" << __FILE__ << ":" << __LINE__ << "]"; \
        abort();                                                \
    }                                                           \
} while(0);
#else
#define CNC_ASSERT(ignore)
#endif

#endif //CONCUSSION_ASSERT_HH
