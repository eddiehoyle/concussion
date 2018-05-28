#ifndef CONCUSSION_EVENT_HH
#define CONCUSSION_EVENT_HH

#include "AbstractEvent.hh"

namespace concussion {

namespace event {

template< typename E >
class Event : public AbstractEvent {

public:

    static const EventTypeId EVENT_TYPE_ID;

public:

    Event() : AbstractEvent( EVENT_TYPE_ID )
    {}

};

template< typename T >
const concussion::event::EventTypeId concussion::event::Event< T >::EVENT_TYPE_ID { typeid( T ).hash_code() };

}

}

#endif //CONCUSSION_EVENT_HH
