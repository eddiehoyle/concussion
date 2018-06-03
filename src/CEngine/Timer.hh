#ifndef CONCUSSION_TIMER_HH
#define CONCUSSION_TIMER_HH

#include <CEngine/Platform.hh>

namespace concussion {

class Timer {

    using Elapsed = std::chrono::duration< f32, std::milli >;

public:

    Timer();
    ~Timer() = default;

    /// Advances timer by input milliseconds.
    void tick( f32 ms );

    /// Resets timer to zero.
    void reset();

    /// Get time stamp from current timer value
    TimeStamp getTimeStamp() const;

private:

    Elapsed m_elapsed;

};

}

#endif //CONCUSSION_TIMER_HH
