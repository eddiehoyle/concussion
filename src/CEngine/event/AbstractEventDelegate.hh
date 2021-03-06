#ifndef CONCUSSION_ABSTRACTEVENTDELEGATE_HH
#define CONCUSSION_ABSTRACTEVENTDELEGATE_HH

#include "../Platform.hh"
#include "AbstractEvent.hh"

namespace concussion {

namespace event {

using EventDelegateID = ObjectID;
using EventDelegateTypeID = TypeID;

class AbstractEventDelegate {

    public:
    virtual void invoke( AbstractEvent* e ) = 0;
    virtual EventDelegateID getDelegateId() const = 0;
    virtual EventDelegateTypeID getStaticEventTypeId() const = 0;
    virtual bool operator==( AbstractEventDelegate* other) const = 0;
    virtual AbstractEventDelegate* clone() = 0;
};

}

}

#endif //CONCUSSION_ABSTRACTEVENTDELEGATE_HH
