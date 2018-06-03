#include "Timer.hh"

namespace concussion {

Timer::Timer() : m_elapsed( 0 ) {}

void Timer::tick( float ms ) {
    m_elapsed += std::chrono::duration< float, std::ratio< 1, 1000>>( ms );
}

void Timer::reset() {
    m_elapsed = Elapsed::zero();
}

TimeStamp Timer::getTimeStamp() const {
    return TimeStamp( this->m_elapsed.count() );
}

} // namespace concussion