#ifndef CONCUSSION_EVENT_HH
#define CONCUSSION_EVENT_HH

#include "AbstractEvent.hh"
#include "../ObjectType.hh"

namespace concussion {

namespace event {

template< typename E >
class Event : public AbstractEvent {

public:

    static const EventTypeID EVENT_TYPE_ID;

public:

    Event() : AbstractEvent( EVENT_TYPE_ID )
    {}

};

template< typename E >
//const concussion::event::EventTypeID concussion::event::Event< E >::EVENT_TYPE_ID { typeid( E ).hash_code() };
const concussion::event::EventTypeID concussion::event::Event< E >::EVENT_TYPE_ID =
        concussion::internal::ObjectTypeID< concussion::event::AbstractEvent >::get< E >();

}

}

#endif //CONCUSSION_EVENT_HH
