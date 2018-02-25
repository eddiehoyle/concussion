#ifndef CONCUSSION_LOG_HH
#define CONCUSSION_LOG_HH

#include <mutex>
#include <ostream>

namespace concussion {

namespace base {

enum class Level {
    Debug,
    Info,
    Warning,
    Error,
};

class Stream;
class NullStream;

class Log {
public:
    Log( std::ostream* stream, Level level );
private:
    std::mutex m_mutex;
    std::ostream* m_stream;
    Level m_level;

    friend Stream;
    friend NullStream;
};

class Stream {
public:
    explicit Stream( Log& log, const std::string& prefix  );
    ~Stream();

    template< typename T >
    Stream& operator<<( T value );

private:
    Stream( Stream& ) = delete;
    Stream& operator=( Stream& ) = delete;
    Stream& operator=( Stream&& ) = delete;

    Log& m_log;
};

template< typename T >
Stream& Stream::operator<<( T value ) {
    *( m_log.m_stream ) << value;
    return *this;
}

class NullStream {
public:
    explicit NullStream( Log& log, const std::string& prefix );
    ~NullStream() = default;

    template< typename T >
    NullStream& operator<<( T value );

private:
    NullStream( NullStream& ) = delete;
    NullStream& operator=( Stream& ) = delete;
    NullStream& operator=( NullStream&& ) = delete;

    Log& m_log;
};

template< typename T >
NullStream& NullStream::operator<<( T value ) {
    return *this;
}

Log& debug_log();
Log& info_log();
Log& warn_log();
Log& error_log();

} // namespace base

} // namespace concussion

#define CNC_INITIALISE_LOG()         \
    ::concussion::base::debug_log(); \
    ::concussion::base::info_log();  \
    ::concussion::base::warn_log();  \
    ::concussion::base::error_log();

#ifdef CNC_LOGGING_ENABLED
#define CNC_DEBUG ::concussion::base::Stream( ::concussion::base::debug_log(), "DBG" ) << "[" << __FUNCTION__ << "]: "
#define CNC_INFO ::concussion::base::Stream( ::concussion::base::info_log(), "NFO" ) << "[" << __FUNCTION__ << "]: "
#define CNC_WARN ::concussion::base::Stream( ::concussion::base::warn_log(), "WRN" ) << "[" << __FUNCTION__ << "]: "
#define CNC_ERROR ::concussion::base::Stream( ::concussion::base::error_log(), "ERR" ) << "[" << __FUNCTION__ << "]: "
#else
#define CNC_DEBUG ::concussion::base::NullStream( ::concussion::base::debug_log(), "DBG" )
#define CNC_INFO ::concussion::base::NullStream( ::concussion::base::info_log(), "NFO" )
#define CNC_WARN ::concussion::base::NullStream( ::concussion::base::warn_log(), "WRN" )
#define CNC_ERROR ::concussion::base::NullStream( ::concussion::base::error_log(), "ERR" )
#endif

#endif //CONCUSSION_LOG_HH
