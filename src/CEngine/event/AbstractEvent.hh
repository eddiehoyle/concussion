#ifndef CONCUSSION_ABSTRACTEVENT_HH
#define CONCUSSION_ABSTRACTEVENT_HH

#include <CEngine/Platform.hh>
#include <CEngine/Assert.hh>
#include <CEngine/Types.hh>

namespace concussion {

namespace event {

using EventTypeId		= TypeID;
using EventTimestamp	= TimeStamp;

class AbstractEvent {

public:

    AbstractEvent( EventTypeId type )
    {}

    EventTypeId getEventTypeID() const { return this->m_type; }
    EventTimestamp getTimeCreated() const { return this->m_time; }

protected:

    EventTypeId m_type;
    EventTimestamp m_time;

};

}

}

#endif //CONCUSSION_ABSTRACTEVENT_HH
