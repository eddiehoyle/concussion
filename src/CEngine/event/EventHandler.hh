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
    void addEventCallback(AbstractEventDelegate* delegate) {

        EventTypeID eventTypeID = E::EVENT_TYPE_ID;

        EventDispatcherMap::iterator iter = this->m_eventDispatcherMap.find(eventTypeID);

        CNC_ERROR << "Adding event callback with ID=" << eventTypeID;

        if (iter != this->m_eventDispatcherMap.end()) {

            CNC_ERROR << "Dispatcher found! Adding callback...";

            this->m_eventDispatcherMap[eventTypeID]->addEventCallback(delegate);

        } else {

            CNC_ERROR << "No dispatcher found... adding new one.";

            std::pair<EventTypeID, AbstractEventDispatcher* > kvp(eventTypeID, new EventDispatcher<E>());
            kvp.second->addEventCallback(delegate);
            this->m_eventDispatcherMap.insert(kvp);

            CNC_ERROR << "dispatcherMap size=" << this->m_eventDispatcherMap.size();
        }

    }

    int getDispatcherCount() {
        return this->m_eventDispatcherMap.size();
    }

    // Remove event callback
    void removeEventCallback(AbstractEventDelegate* delegate) {

//        auto typeId = delegate->getStaticEventTypeId();
//        EventDispatcherMap::const_iterator iter = this->m_eventDispatcherMap.find(typeId);
//        if (iter != this->m_eventDispatcherMap.end()) {
//            this->m_eventDispatcherMap[typeId]->removeEventCallback(delegate);
//        }
    }

    template<class E, class... ARGS>
    void send( ARGS&&... eventArgs ) {

        CNC_ERROR << "dispatcherMap size=" << this->m_eventDispatcherMap.size();

        // check if type of object is trivially copyable
        static_assert( std::is_trivially_copyable<E>::value, "Event is not trivially copyable." );

        auto event = new E(std::forward<ARGS>(eventArgs)...);

        CNC_ERROR << "sending event type=" << event->getEventTypeID();

        // Buffer
        this->m_eventStorage.push_back( event );
    }

    void dispatch() {

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
            CNC_ERROR << "looking for dispatcher with event type id=" << event->getEventTypeID();
            if (it == this->m_eventDispatcherMap.end()) {
                continue;
            }

            CNC_ERROR << "found one!!";


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


    using EventDispatcherMap = std::map< EventTypeID, AbstractEventDispatcher* >;
    using EventStorage = std::vector< AbstractEvent* >;

    EventDispatcherMap m_eventDispatcherMap;
    EventStorage m_eventStorage;

};

}

}

#endif //CONCUSSION_EVENTHANDLER_HH
