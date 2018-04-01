#include "Model.hh"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

namespace concussion {

struct Face {

    /// TODO
    unsigned int offset;

    /// The number of indices, eg: '3/2/2' == 3
    unsigned int num_indices;
};

struct Indices {

    /// Constructor
    Indices()
            : vertex( -1 ),
              uv( -1 ),
              normal( -1 ) {}

    /// Constrcut with values
    explicit Indices( int vertex, int uv, int normal )
            : vertex( vertex ),
              uv( uv ),
              normal( normal ) {}

    /// Vertex index
    int vertex;

    /// Texture coordinate index
    int uv;

    /// Normal index
    int normal;
};

inline bool operator<( const Indices& a, const Indices& b ) {
    if ( a.vertex != b.vertex ) return ( a.vertex < b.vertex );
    if ( a.normal != b.normal ) return ( a.normal < b.normal );
    if ( a.uv != b.uv ) return ( a.uv < b.uv );
    return false;
}

template< typename OutT >
static void split( const std::string& string, char delim, OutT result ) {
    std::stringstream stream( string );
    std::string item;
    while ( std::getline( stream, item, delim ) ) {
        *( result++ ) = item;
    }
}

static std::vector< std::string > split( const std::string& string, char delimiter ) {
    std::vector< std::string > elems;
    split( string, delimiter, std::back_inserter( elems ) );
    return elems;
}

/// Trim left whitespace
inline void ltrim( std::string& string ) {
    string.erase( string.begin(), std::find_if( string.begin(), string.end(), []( int ch ) {
        return !std::isspace( ch );
    } ) );
}

/// Trim right whitespace
inline void rtrim( std::string& s ) {
    s.erase( std::find_if( s.rbegin(), s.rend(), []( int ch ) {
        return !std::isspace( ch );
    } ).base(), s.end() );
}

/// Trim both ends
inline void trim( std::string& s ) {
    ltrim( s );
    rtrim( s );
}

/// String to integer
inline int toInt( const std::string& num ) {
    return static_cast< int >( atoi( num.c_str() ) );
}

/// String to float
inline float toFloat( const std::string& num ) {
    return static_cast< float >( atof( num.c_str() ) );
}

/// Reorder vertices with face indices
static unsigned int align_vertices( std::map< Indices, unsigned int >& cache,
                                    std::vector< float >& vertices,
                                    std::vector< float >& uvs,
                                    std::vector< float >& normals,
                                    const std::vector< float >& in_vertices,
                                    const std::vector< float >& in_uvs,
                                    const std::vector< float >& in_normals,
                                    const Indices& indices ) {

    // Found cache
    const std::map< Indices, unsigned int >::iterator it = cache.find( indices );
    if ( it != cache.end() ) {
        return it->second;
    }

    // Grab vertices
    vertices.push_back( in_vertices[3 * indices.vertex + 0] );
    vertices.push_back( in_vertices[3 * indices.vertex + 1] );
    vertices.push_back( in_vertices[3 * indices.vertex + 2] );

    // Grab normals
    normals.push_back( in_normals[3 * indices.normal + 0] );
    normals.push_back( in_normals[3 * indices.normal + 1] );
    normals.push_back( in_normals[3 * indices.normal + 2] );

    // uvss
    uvs.push_back( in_uvs[2 * indices.uv + 0] );
    uvs.push_back( 1 - in_uvs[2 * indices.uv + 1] );

    // Find the index for this vertex
    unsigned int index = static_cast< unsigned int >( vertices.size() / 3 - 1 );

    // Cache
    cache[indices] = index;

    return index;
}

/// Reorder data by indices
static bool align_geometry( std::vector< float >& vertices,
                            std::vector< float >& uvs,
                            std::vector< float >& normals,
                            std::vector< unsigned int >& vertex_indices,
                            const std::vector< Indices >& in_indices,
                            const std::vector< Face >& in_faces ) {

    if ( in_faces.empty() ) {
        return false;
    }

    // Temporary containers to store ordered data
    std::vector< float > ordered_vertices;
    std::vector< float > ordered_uvs;
    std::vector< float > ordered_normals;
    std::vector< unsigned int > ordered_vertex_indices;

    // Index cache < indices, result_vertex_index >
    std::map< Indices, unsigned int > cache;

    // Flatten vertices and indices
    for ( const Face& face : in_faces ) {

        // First bunch of indices for this face
        Indices indices0 = in_indices[face.offset];

        //
        Indices indices1;
        indices1.vertex = -1;
        indices1.uv = -1;
        indices1.normal = -1;

        // Next indices for this face
        Indices indices2 = in_indices[face.offset + 1];

        unsigned int npolys = face.num_indices;

        // Polygon -> triangle fan conversion
        // The '2' is cause we grabbed first and second offset index above?
        for ( std::size_t k = 2; k < npolys; k++ ) {

            indices1 = indices2;
            indices2 = in_indices[face.offset + k];

            unsigned int vertex_index0 = align_vertices( cache,
                                                         ordered_vertices, ordered_uvs, ordered_normals,
                                                         vertices, uvs, normals,
                                                         indices0 );
            unsigned int vertex_index1 = align_vertices( cache,
                                                         ordered_vertices, ordered_uvs, ordered_normals,
                                                         vertices, uvs, normals,
                                                         indices1 );
            unsigned int vertex_index2 = align_vertices( cache,
                                                         ordered_vertices, ordered_uvs, ordered_normals,
                                                         vertices, uvs, normals,
                                                         indices2 );

            ordered_vertex_indices.push_back( vertex_index0 );
            ordered_vertex_indices.push_back( vertex_index1 );
            ordered_vertex_indices.push_back( vertex_index2 );
        }
    }

    /// Move data
    vertices.swap( ordered_vertices );
    uvs.swap( ordered_uvs );
    normals.swap( ordered_normals );
    vertex_indices.swap( ordered_vertex_indices );

    return true;
}

void load_obj( const std::string& path, graphics::Shape& shape ) {

    std::ifstream stream( path.c_str() );
    if ( !stream ) {
        std::cerr << __func__ << " : path does not exist: " << path << std::endl;
        return;
    }

    // Declare some containers
    std::vector< float > vertices, uvs, normals;
    vertices.reserve( 1024 << 4 );
    uvs.reserve( 1024 << 4 );
    normals.reserve( 1024 << 4 );

    // Indices
    std::vector< Indices > all_indices;
    all_indices.reserve( 1024 << 4 );

    // Faces
    std::vector< Face > all_faces;
    all_faces.reserve( 1024 << 4 );

    std::map< int, Material > material_map;

    // Line buffer
    std::string linebuffer;
    linebuffer.reserve( 512 );

    while ( stream.peek() != -1 ) {

        // Read line
        linebuffer.resize( 0 );
        std::getline( stream, linebuffer );

        // Trim whitespace
        trim( linebuffer );

        // Skip empty lines
        if ( linebuffer.empty() ) {
            continue;
        }

        // Split line on spaces
        std::vector< std::string > pieces = split( linebuffer, ' ' );
        if ( pieces.empty() ) {
            continue;
        }

        // Grab token and string bits
        const std::string token( pieces[0] );
        pieces.erase( pieces.begin() );

        // Comments
        if ( token == "#" ) {
            continue;
        }

        // Vertices
        if ( token == "v" ) {
            vertices.push_back( toFloat( pieces[0] ) );
            vertices.push_back( toFloat( pieces[1] ) );
            vertices.push_back( toFloat( pieces[2] ) );
            continue;
        }

        // Textures
        if ( token == "vt" ) {
            uvs.push_back( toFloat( pieces[0] ) );
            uvs.push_back( toFloat( pieces[1] ) );
            continue;
        }

        // Normals
        if ( token == "vn" ) {
            normals.push_back( toFloat( pieces[0] ) );
            normals.push_back( toFloat( pieces[1] ) );
            normals.push_back( toFloat( pieces[2] ) );
            continue;
        }

        // Faces
        if ( token == "f" ) {

            // Create a face
            Face face;
            face.offset = static_cast< unsigned int >( all_indices.size() );
            face.num_indices = 0;

            // Loop through pieces
            for ( const std::string& part : pieces ) {

                // Split indices into vector, eg: "1/1/2" to { "1", "1", "2" }
                const std::vector< std::string > pointIndices = split( part, '/' );

                // Create index
                Indices indices;
                indices.vertex = toInt( pointIndices[0] ) - 1;
                indices.uv = toInt( pointIndices[1] ) - 1;
                indices.normal = toInt( pointIndices[2] ) - 1;

                // Cache
                all_indices.push_back( indices );
                face.num_indices++;
            }

            // Cache
            all_faces.push_back( face );

            continue;
        }
    }

    std::vector< unsigned int > vertex_indices;
    align_geometry( vertices, uvs, normals, vertex_indices, all_indices, all_faces );

    // Update output
    shape.vertices = vertices;
    shape.uvs = uvs;
    shape.normals = normals;
    shape.indices = vertex_indices;

}

} // namespace concussion