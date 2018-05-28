#ifndef CONCUSSION_EVENTHANDLER_HH
#define CONCUSSION_EVENTHANDLER_HH

#include <utility>
#include <map>
#include <vector>
#include <CEngine/Log.hh>

#include "AbstractEvent.hh"
#include "AbstractEventDispatcher.hh"
#include "EventDispatcher.hh"

namespace concussion {

namespace event {

class EventHandler {

public:

    EventHandler() = default;
    ~EventHandler() = default;

    // Add event callback
    template<class E>
    void addEventCallback(AbstractEventDelegate* const delegate) {

        EventTypeId ETID = E::STATIC_EVENT_TYPE_ID;

        EventDispatcherMap::const_iterator iter = this->m_eventDispatcherMap.find(ETID);
        if (iter == this->m_eventDispatcherMap.end()) {
            std::pair<EventTypeId, AbstractEventDispatcher*> kvp(ETID, new EventDispatcher<E>());

            kvp.second->addEventCallback(delegate);

            this->m_eventDispatcherMap.insert(kvp);
        } else {
            this->m_eventDispatcherMap[ETID]->addEventCallback(delegate);
        }

    }

    // Remove event callback
    void removeEventCallback(AbstractEventDelegate* delegate) {

        auto typeId = delegate->getStaticEventTypeId();
        EventDispatcherMap::const_iterator iter = this->m_eventDispatcherMap.find(typeId);
        if (iter != this->m_eventDispatcherMap.end()) {
            this->m_eventDispatcherMap[typeId]->removeEventCallback(delegate);
        }
    }

    template<class E, class... ARGS>
    void send( ARGS&&... eventArgs ) {

        // check if type of object is trivially copyable
        static_assert( std::is_trivially_copyable<E>::value, "Event is not trivially copyable." );

        // Buffer
        this->m_eventStorage.push_back(new E(std::forward<ARGS>(eventArgs)...));
    }

    void dispatch()
    {
        size_t lastIndex = this->m_eventStorage.size();
        size_t thisIndex = 0;

        CNC_ERROR << "storage=" << lastIndex;

        while (thisIndex < lastIndex) {
            auto event = this->m_eventStorage[thisIndex++];
            if (event == nullptr) {
                CNC_ERROR << "Skip corrupted event: " << event->getEventTypeID();
                continue;
            }

            auto it = this->m_eventDispatcherMap.find( event->getEventTypeID());
            CNC_ERROR << "found dispatcher=" << (it != this->m_eventDispatcherMap.end());
            if (it == this->m_eventDispatcherMap.end()) {
                continue;
            }

            it->second->dispatch(event);

            // update last index, after dispatch operation there could be new events
            lastIndex = this->m_eventStorage.size();
        }

        // reset
        clearEventBuffer();
    }

    void clearEventBuffer() {
        this->m_eventStorage.clear();
    }

    inline void clearEventDispatcher() {
        this->m_eventDispatcherMap.clear();
    }

private:


    using EventDispatcherMap = std::map< EventTypeId, AbstractEventDispatcher* >;
    using EventStorage = std::vector< AbstractEvent* >;

    EventDispatcherMap m_eventDispatcherMap;
    EventStorage m_eventStorage;

};

}

}

#endif //CONCUSSION_EVENTHANDLER_HH
