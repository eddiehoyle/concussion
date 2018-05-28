#ifndef CONCUSSION_EVENTDISPATCHER_HH
#define CONCUSSION_EVENTDISPATCHER_HH

#include "AbstractEventDispatcher.hh"

namespace concussion {
namespace event {

template< typename T >
class EventDispatcher : public AbstractEventDispatcher
{

    using EventDelegateList			= std::list< AbstractEventDelegate* >;

    //using PendingAddDelegates		= std::list< AbstractEventDelegate* >;
    using PendingRemoveDelegates	= std::list< AbstractEventDelegate* >;

    //PendingAddDelegates		m_PendingAddDelegates;
    PendingRemoveDelegates	m_pendingRemoveDelegates;
    EventDelegateList		m_eventCallbacks;
    bool					m_locked;

public:

    // never use!
    EventDispatcher() :
            m_pendingRemoveDelegates(),
            m_eventCallbacks(),
            m_locked(false)
    {}

    virtual ~EventDispatcher()
    {
        //this->m_PendingAddDelegates.clear();
        this->m_pendingRemoveDelegates.clear();
        this->m_eventCallbacks.clear();
    }

    inline void dispatch(AbstractEvent* event) override {
    }

    virtual void addEventCallback( AbstractEventDelegate* const eventDelegate ) override {
    }

    virtual void removeEventCallback( AbstractEventDelegate* eventDelegate ) override {
    }

    virtual inline std::size_t getEventCallbackCount() const override {
        return this->m_eventCallbacks.size();
    }
};

}

}

#endif //CONCUSSION_EVENTDISPATCHER_HH
