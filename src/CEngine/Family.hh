#ifndef CONCUSSION_FAMILY_HH
#define CONCUSSION_FAMILY_HH

namespace concussion {

namespace internal {

template<class T>
class FamilyTypeID {

public:

    template<class U>
    static const unsigned int get() {
        static const unsigned int STATIC_TYPE_ID {
                s_count++
        };
        return STATIC_TYPE_ID;
    }

    static const unsigned int get() {
        return s_count;
    }

private:
    static unsigned int s_count;
};

} // namespace internal

} // namespace concussion

#endif //CONCUSSION_FAMILY_HH
