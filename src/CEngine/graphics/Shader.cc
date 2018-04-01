#include "Shader.hh"

#include "IO.hh"
#include "Log.hh"
#include "Assert.hh"
#include "Resource.hh"


namespace concussion {

namespace graphics {
//
//void load( const std::string& vertex_source,
//           const std::string& fragment_source,
//           bool& result ) {
//}
//
//
//void validate_shader( GLuint shader ) {
//
//    GLint result = GL_FALSE;
//    glGetShaderiv( shader, GL_COMPILE_STATUS, &result );
//
//    if  ( !result ) {
//
//        int len;
//        GLint length;
//        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &length );
//
//        GLchar* error = new GLchar[length + 1];
//        glGetShaderInfoLog( shader, length, nullptr, error );
//        CNC_ERROR << error;
//        delete[] error;
//    }
//    CNC_ASSERT( result );
//}
//
//
//void validate_program( GLuint program ) {
//
//    GLint result = GL_FALSE;
//    glGetProgramiv( program, GL_LINK_STATUS, &result );
//
//    if  ( !result ) {
//
//        GLint length;
//        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &length );
//
//        GLchar* error = new GLchar[length + 1];
//        glGetProgramInfoLog( program, length, nullptr, error );
//        CNC_ERROR << error;
//        delete[] error;
//    }
//    CNC_ASSERT( result );
//}
//
//
//GLuint compile( const std::string& source, GLenum type ) {
//    GLuint id = glCreateShader( type );
//    const char* c_source = source.c_str();
//    glShaderSource( id, 1, &c_source, nullptr );
//    glCompileShader( id );
//    validate_shader( id );
//    return id;
//}
//
//SimpleShader::SimpleShader()
//        : m_program( 0 ),
//          m_vertex( 0 ),
//          m_fragment( 0 ),
//          m_uniforms() {
//
//    // TODO
//    // Just write these shaders as standalone classes
//    // Don't bother with abstractions and adding complexity
//    // Create shaders here, bind and link, that's all
//    // Handle uniforms in ShaderDomain
//
//    bool vertex_shader_exists;
//    const std::string vertex_path = io::find_resource( "shaders/simple_vertex.glsl", vertex_shader_exists );
//    CNC_ASSERT( vertex_shader_exists );
//    const std::string vertex_source = io::read_file( vertex_path );
//
//    bool fragment_shader_exists;
//    const std::string fragment_path = io::find_resource( "shaders/simple_fragment.glsl", fragment_shader_exists );
//    CNC_ASSERT( fragment_shader_exists );
//    const std::string fragment_source = io::read_file( fragment_path );
//
//    m_vertex = compile( vertex_source, GL_VERTEX_SHADER );
//    m_fragment = compile( fragment_source, GL_FRAGMENT_SHADER );
//
//    m_program = glCreateProgram();
//    glAttachShader( m_program, m_vertex );
//    glAttachShader( m_program, m_fragment );
//
//    glBindAttribLocation( m_program, 0, "i_position" );
//
//    glLinkProgram( m_program );
//    validate_program( m_program );
//
//    GLuint model_matrix;
//    initialise_uniform( "u_modelMatrix", &model_matrix );
//    m_uniforms["u_modelMatrix"] = model_matrix;
//
//    GLuint view_matrix;
//    initialise_uniform( "u_viewMatrix", &view_matrix );
//    m_uniforms["u_viewMatrix"] = view_matrix;
//
//    GLuint projection_matrix;
//    initialise_uniform( "u_projectionMatrix", &projection_matrix );
//    m_uniforms["u_projectionMatrix"] = projection_matrix;
//}
//
//SimpleShader::~SimpleShader() {
//    glDetachShader( m_program, m_vertex );
//    glDetachShader( m_program, m_fragment );
//    glDeleteShader( m_vertex );
//    glDeleteShader( m_fragment );
//    glDeleteProgram( m_program );
//}
//
//GLuint SimpleShader::program() const {
//    CNC_ASSERT( glIsProgram( m_program ) );
//    return m_program;
//}
//
//void SimpleShader::find_uniform( const char* name, GLuint* uniform ) {
//    auto iter = m_uniforms.find( name );
//    CNC_ASSERT( iter != m_uniforms.end() );
//    *uniform = iter->second;
//}
//
//void SimpleShader::initialise_uniform( const char *name, GLuint *uniform ) {
//    GLint location = glGetUniformLocation( m_program, name );
//    CNC_ASSERT( location >= 0 );
//    *uniform = static_cast< GLuint >( location );
//}

} // namespace graphics

} // namespace concussion
