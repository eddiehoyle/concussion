#ifndef CONCUSSION_ABSTRACTEVENTDISPATCHER_HH
#define CONCUSSION_ABSTRACTEVENTDISPATCHER_HH

#include "../Platform.hh"
#include "AbstractEvent.hh"
#include "AbstractEventDelegate.hh"

namespace concussion {
namespace event {

using EventDelegateId = TypeID;

class AbstractEventDispatcher {

public:

    virtual ~AbstractEventDispatcher()
    {}

    virtual void dispatch( AbstractEvent* event ) = 0;
    virtual void addEventCallback( AbstractEventDelegate* const delegate ) = 0;
    virtual void removeEventCallback( AbstractEventDelegate* delegate ) = 0;
    virtual inline std::size_t getEventCallbackCount() const = 0;
};

}

}

#endif //CONCUSSION_ABSTRACTEVENTDISPATCHER_HH
