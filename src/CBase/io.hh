#ifndef CONCUSSION_IO_HH
#define CONCUSSION_IO_HH

#include "log.hh"

namespace concussion {

namespace io {

/// Open a text file and return it's contents.
/// @param path A text file.
/// @returns The contents of the file.
std::string read_file( const std::string& i_path );

} // namespace base

} // namespace concussion

#endif //CONCUSSION_IO_HH
