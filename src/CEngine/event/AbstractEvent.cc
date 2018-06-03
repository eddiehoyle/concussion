#include "AbstractEvent.hh"
#include "API.hh"
#include "Timer.hh"

namespace concussion {
namespace event {

AbstractEvent::AbstractEvent( EventTypeID type )
    : m_type( type ),
      m_time() {
    m_time = CNC_Engine->CNC_EngineTime->getTimeStamp();
}

}
}