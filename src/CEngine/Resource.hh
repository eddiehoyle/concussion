#ifndef CONCUSSION_RESOURCE_HH
#define CONCUSSION_RESOURCE_HH

#include <string>

namespace concussion {

namespace io {

/// Look up a resource path
/// @param path Relative path to a file in 'resources/' directory.
/// @param[out] result If file exists or not.
/// @returns The full path used to find the resource.
std::string find_resource( const std::string& i_path, bool& o_result );

}

};

#endif //CONCUSSION_RESOURCE_HH
