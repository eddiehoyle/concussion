#include "family.hh"

namespace concussion {

class AbstractEntity;
class IComponent;
class ISystem;

namespace internal {

template <>
unsigned int FamilyTypeID< AbstractEntity >::s_count = 0u;

template <>
unsigned int FamilyTypeID< IComponent >::s_count = 0u;

template <>
unsigned int FamilyTypeID< ISystem >::s_count = 0u;

template class FamilyTypeID< AbstractEntity >;
template class FamilyTypeID< IComponent >;
template class FamilyTypeID< ISystem >;

} // namespace internal

} // namespace concussion
