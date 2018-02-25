//
// Created by Eddie Hoyle on 24/02/18.
//

#include "io.hh"

#include <fstream>

namespace concussion {

namespace io {

std::string read_file( const std::string& i_path ) {

    std::string data;
    std::ifstream stream( i_path, std::ios::in );
    if ( !stream.good() ) {
        CNC_ERROR << "File does not exist: " << i_path;
        return std::string();
    }

    if ( stream.is_open() ) {
        std::string line;
        while ( getline( stream, line ) )
            data += "\n" + line;
        stream.close();
    }
    return data;
}

} // namespace base

} // namespace concussion





