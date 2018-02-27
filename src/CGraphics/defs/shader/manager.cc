#include <CBase/log.hh>
#include <CBase/assert.hh>

#include "manager.hh"

namespace concussion {

namespace graphics {


void validate_shader( GLuint shader ) {

    GLint result = GL_FALSE;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &result );

    if  ( !result ) {

        int len;
        GLint length;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &length );

        GLchar* error = new GLchar[length + 1];
        glGetShaderInfoLog( shader, length, nullptr, error );
        CNC_ERROR << error;
        delete[] error;
    }
    CNC_ASSERT( result );
}


void validate_program( GLuint program ) {

    GLint result = GL_FALSE;
    glGetProgramiv( program, GL_LINK_STATUS, &result );

    if  ( !result ) {

        GLint length;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &length );

        GLchar* error = new GLchar[length + 1];
        glGetProgramInfoLog( program, length, nullptr, error );
        CNC_ERROR << error;
        delete[] error;
    }
    CNC_ASSERT( result );
}


GLuint compile( const std::string& source, GLenum type ) {
    GLuint id = glCreateShader( type );
    const char* c_source = source.c_str();
    glShaderSource( id, 1, &c_source, nullptr );
    glCompileShader( id );
    return id;
}

void bind_attributes( const ShaderSource& source, ShaderTargetPtr& shader ) {
    for ( std::size_t i = 0; i < source.attributes.size(); ++i ) {
        glBindAttribLocation( shader->program,
                              static_cast< GLuint >( i ),
                              source.attributes[ i ] );
        shader->attributes[ source.attributes[i] ] = static_cast< GLuint >( i );
    }
}
void bind_uniforms( const ShaderSource& source, ShaderTargetPtr& shader ) {
    for ( const auto& uniform : source.uniforms ) {
        GLint location = glGetUniformLocation( shader->program, uniform );
        shader->uniforms[ uniform ] = static_cast< GLuint >( location );
    }
}

void validate_attributes( const ShaderTargetPtr& shader ) {
    for ( const auto& attribute : shader->attributes ) {
        GLint location = glGetAttribLocation( shader->program, attribute.first );
        CNC_ASSERT( location >= 0 );
    }
}

void validate_uniforms( const ShaderTargetPtr& shader ) {
    for ( const auto& uniform : shader->uniforms ) {
        GLint location = glGetUniformLocation( shader->program, uniform.first );
        CNC_ASSERT( location >= 0 );
    }
}

ShaderManager* ShaderManager::s_instance = nullptr;

ShaderManager* ShaderManager::instance() {
    if ( s_instance == nullptr ) {
        s_instance = new ShaderManager();
    }
    return s_instance;
}

ShaderManager::~ShaderManager() {
    delete s_instance;
}

void ShaderManager::add( const ShaderSource& source ) {

    ShaderTargetPtr shader( new ShaderTarget );

    shader->vertex = compile( source.vertex, GL_VERTEX_SHADER );
    validate_shader( shader->vertex );

    shader->fragment = compile( source.fragment, GL_FRAGMENT_SHADER );
    validate_shader( shader->fragment );

    shader->program = glCreateProgram();
    glAttachShader( shader->program, shader->vertex );
    glAttachShader( shader->program, shader->fragment );

    bind_attributes( source, shader );

    glLinkProgram( shader->program );
    validate_program( shader->program );

    bind_uniforms( source, shader );

    // Debug
    validate_attributes( shader );
    validate_uniforms( shader );

    m_shaders[ source.name ] = std::move( shader );
}

void ShaderManager::remove( const char *name ) {

}

void ShaderManager::bind( const char *name ) {

}

void ShaderManager::unbind() {

}


} // namespace graphics

} // namespace concussion