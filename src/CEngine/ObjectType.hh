#ifndef CONCUSSION_TYPE_HH
#define CONCUSSION_TYPE_HH

#include "Platform.hh"
#include "Log.hh"

namespace concussion {

namespace internal {

template< typename T >
class ObjectTypeID{

public:
    template< typename U >
    static const TypeID get() {
        static const TypeID STATIC_TYPE_ID { s_count++ };
        return STATIC_TYPE_ID;
    }

private:
    static TypeID s_count;

};

template<typename T>
concussion::TypeID ObjectTypeID<T>::s_count = 0u;

} // namespace internal

} // namespace concussion

#endif // CONCUSSION_TYPE_HH
