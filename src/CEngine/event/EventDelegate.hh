#ifndef CONCUSSION_EVENTDELEGATE_HH
#define CONCUSSION_EVENTDELEGATE_HH

#include "AbstractEventDelegate.hh"

namespace concussion {

namespace event {

template< typename Class, typename EventType >
class EventDelegate : public AbstractEventDelegate {

    typedef void(Class::*Callback)( EventType* );

    Class *m_receiver;
    Callback m_callback;

public:

    EventDelegate( Class *receiver,
                   Callback& callbackFunction )
            : m_receiver( receiver ),
              m_callback( callbackFunction )
    {}

    virtual AbstractEventDelegate* clone() override {
        return new EventDelegate( this->m_receiver, this->m_callback );
    }

    virtual inline void invoke( const AbstractEvent *const e ) override {
        ( m_receiver->*m_callback )( reinterpret_cast<const EventType *const>(e) );
    }

    virtual inline EventDelegateID getDelegateId() const override {
        static const EventDelegateID DELEGATE_ID{ typeid( Class ).hash_code() ^ typeid( Callback ).hash_code() };
        return DELEGATE_ID;
    }


    virtual inline EventDelegateTypeID getStaticEventTypeId() const override {
        static const EventDelegateTypeID SEID{ EventType::EVENT_TYPE_ID };
        return SEID;
    }

    virtual bool operator==( AbstractEventDelegate *other ) const override {
        if ( this->getDelegateId() != other->getDelegateId() ) {
            return false;
        }
        EventDelegate* delegate = dynamic_cast< EventDelegate* >( other );
        if ( delegate == nullptr ) {
            return false;
        }
        return ( ( this->m_callback == delegate->m_callback ) &&
                 ( this->m_receiver == delegate->m_receiver ) );
    }

};

}

}

#endif //CONCUSSION_EVENTDELEGATE_HH
