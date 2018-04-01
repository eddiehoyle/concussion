#include "Resource.hh"
#include "Log.hh"

#include <ios>
#include <fstream>

namespace concussion {

namespace io {

std::string find_resource( const std::string& path, bool& result ) {

    // Create full resource path
    std::string full_path = CNC_RESOURCES_DIR;
    full_path += "/";
    full_path += path;

    // Get results
    std::ifstream stream( full_path, std::ios::in );
    result = stream.good();
    stream.close();
    return full_path;
}

}

}
