#ifndef CONCUSSION_ABSTRACTEVENT_HH
#define CONCUSSION_ABSTRACTEVENT_HH

#include <CEngine/Platform.hh>
#include <CEngine/Assert.hh>
#include <CEngine/Types.hh>

namespace concussion {

namespace event {

using EventTypeID		= TypeID;
using EventTimestamp	= TimeStamp;

class AbstractEvent {

public:

    AbstractEvent( EventTypeID type )
            : m_type( type ),
              m_time()
    {}

    EventTypeID getEventTypeID() const { return this->m_type; }
    EventTimestamp getTimeCreated() const { return this->m_time; }

protected:

    EventTypeID m_type;
    EventTimestamp m_time;

};

}

}

#endif //CONCUSSION_ABSTRACTEVENT_HH
