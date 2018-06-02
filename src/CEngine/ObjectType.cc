#include "ObjectType.hh"

namespace concussion {

class AbstractEntity;
class AbstractComponent;
class AbstractSystem;
class AbstractEvent;

namespace internal {

template <>
TypeID ObjectTypeID<AbstractEntity>::s_count = 0u;

template <>
TypeID ObjectTypeID<AbstractComponent>::s_count = 0u;

template <>
TypeID ObjectTypeID<AbstractSystem>::s_count = 0u;

template <>
TypeID ObjectTypeID<AbstractEvent>::s_count = 0u;

template class ObjectTypeID<AbstractEntity>;
template class ObjectTypeID<AbstractComponent>;
template class ObjectTypeID<AbstractSystem>;
template class ObjectTypeID<AbstractEvent>;

} // namespace internal

} // namespace concussion
