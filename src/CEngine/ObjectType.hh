#ifndef CONCUSSION_TYPE_HH
#define CONCUSSION_TYPE_HH

#include "Platform.hh"

namespace concussion {

namespace internal {

template<class T>
class FamilyTypeID{

    static TypeID s_count;

public:

    template<class U>
    static const TypeID Get() {
        static const TypeID STATIC_TYPE_ID { s_count++ };
        return STATIC_TYPE_ID;
    }

    static const TypeID Get() {
        return s_count;
    }
};

} // namespace internal

} // namespace concussion

#endif // CONCUSSION_TYPE_HH
