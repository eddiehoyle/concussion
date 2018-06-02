#ifndef CONCUSSION_EVENTDISPATCHER_HH
#define CONCUSSION_EVENTDISPATCHER_HH

#include "AbstractEventDispatcher.hh"

namespace concussion {
namespace event {

/// Un/Registers subscribers for events and dispatches forwards incoming events.
/// Add and remove subscribers for events, and dispatch events to subscribers.
/// \tparam T
template< typename T >
class EventDispatcher : public AbstractEventDispatcher {

    using EventDelegateList         = std::list< AbstractEventDelegate * >;
    using PendingAddDelegates       = std::list< AbstractEventDelegate * >;
    using PendingRemoveDelegates    = std::list< AbstractEventDelegate * >;

    PendingAddDelegates m_pendingAddDelegates;
    PendingRemoveDelegates m_pendingRemoveDelegates;
    EventDelegateList m_eventCallbacks;
    bool m_locked;

public:

    // never use!
    EventDispatcher()
            : m_pendingAddDelegates(),
              m_pendingRemoveDelegates(),
              m_eventCallbacks(),
              m_locked( false ) {}

    virtual ~EventDispatcher() {
        this->m_pendingAddDelegates.clear();
        this->m_pendingRemoveDelegates.clear();
        this->m_eventCallbacks.clear();
    }

    /// Dispatch events to all subscribers.
    /// EventHandler calls this function. I think can be multiple dispatchers?
    /// @param event
    inline void dispatch( AbstractEvent *event ) override {

        CNC_ERROR << "Dispatcher... dispatching!!";

        // Also, clean up pending remove delegates here
        // ;

        // Pass events to all subscribers
        for ( auto callback : this->m_eventCallbacks ) {
            CNC_ASSERT( callback != nullptr && "Invalid event callback." );
            callback->invoke( event );
        }
    }

    virtual void addEventCallback( AbstractEventDelegate* eventDelegate ) override {

        CNC_ERROR << "Adding event delegate!";

        // Check if eventDelegate is in pending 'to be removed' delegates
        // ;

        // Otherwise, add th delegate
        this->m_eventCallbacks.push_back( eventDelegate );
    }

    virtual void removeEventCallback( AbstractEventDelegate *eventDelegate ) override {

    }

    virtual inline std::size_t getEventCallbackCount() const override {
        return this->m_eventCallbacks.size();
    }
};

}

}

#endif //CONCUSSION_EVENTDISPATCHER_HH
