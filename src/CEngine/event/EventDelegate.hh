#ifndef CONCUSSION_EVENTDELEGATE_HH
#define CONCUSSION_EVENTDELEGATE_HH

namespace concussion {

namespace event {

template< typename Class, typename EventType >
class EventDelegate : public IEventDelegate {

    typedef void(Class::*Callback)( const EventType *const );

    Class *m_Receiver;
    Callback m_Callback;

};

}

}

#endif //CONCUSSION_EVENTDELEGATE_HH
