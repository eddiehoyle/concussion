#ifndef CONCUSSION_OPENGL_HH
#define CONCUSSION_OPENGL_HH

#include <GL/glew.h>

/** __glGetLastErrorImpl
	This method implements a mechanism that checks the last OpenGL errors
	that occured since the last time this.
*/
void __glGetLastErrorImpl(const char* file, int line, const char *func);

/** glGetLastError
	This is a convinient macro which invokes the implementation of glCheckError
	with the right file name and line number.
*/
#ifdef _DEBUG
#define glGetLastError() __glGetLastErrorImpl( __FILE__, __LINE__, __FUNCTION__ )
#else
#define glGetLastError()
#endif


#endif //CONCUSSION_OPENGL_HH
