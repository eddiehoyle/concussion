#include "ObjectType.hh"

namespace concussion {

class AbstractEntity;
class AbstractComponent;
class AbstractSystem;

namespace internal {

template <>
TypeID FamilyTypeID<AbstractEntity>::s_count			= 0u;

template <>
TypeID FamilyTypeID<AbstractComponent>::s_count		= 0u;

template <>
TypeID FamilyTypeID<AbstractSystem>::s_count			= 0u;

template class FamilyTypeID<AbstractEntity>;
template class FamilyTypeID<AbstractComponent>;
template class FamilyTypeID<AbstractSystem>;

} // namespace internal

} // namespace concussion
