#ifndef CONCUSSION_ABSTRACTEVENTLISTENER_HH
#define CONCUSSION_ABSTRACTEVENTLISTENER_HH

#include "Event.hh"
#include "../API.hh"
#include "AbstractEventDelegate.hh"
#include "EventDelegate.hh"

#include <type_traits>
#include <functional>

namespace concussion {

namespace event {

/// Allows for derived classes to listen to events.
///
class AbstractEventListener {

private:

    using RegisteredCallbacks = std::list< AbstractEventDelegate * >;
    RegisteredCallbacks m_registeredCallbacks;

public:

    AbstractEventListener() = default;

    virtual ~AbstractEventListener() = default;

    /// @param C This is the callback executed when event E is sent
    /// @param E Listen for this event
    /// @param Callback Uhhh
    template< typename C, typename E >
    void registerEventCallback( void(C::*Callback)( E* ) ) {
        AbstractEventDelegate *eventDelegate = new EventDelegate< C, E >( static_cast< C* >(this), Callback );
        m_registeredCallbacks.push_back( eventDelegate );
        CNC_Engine->subscribeEvent< E >( eventDelegate );
    }

    template< typename C, typename E >
    void unregisterEventCallback( void(C::*Callback)( const E *const ) ) {
    }
};

}

}

#endif //CONCUSSION_ABSTRACTEVENTLISTENER_HH
