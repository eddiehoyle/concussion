#ifndef CONCUSSION_GLBUFFER_HH
#define CONCUSSION_GLBUFFER_HH

#include <GL/glew.h>
#include <CEngine/Assert.hh>

#include "GLUtil.hh"

namespace concussion {

using VertexBufferID = GLuint;

struct VertexArray {

    GLuint			m_ID;

    VertexArray()
    {
        glGenVertexArrays(1, &this->m_ID);
        glBindVertexArray(this->m_ID);
        glBindVertexArray(0);

        glGetLastError();
    }

    ~VertexArray()
    {
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &this->m_ID);

        glGetLastError();
    }

    inline void Bind() const
    {
        glBindVertexArray(this->m_ID);
    }

    inline void Unbind() const
    {
        glBindVertexArray(0);
    }
};

struct VertexBuffer {

    GLuint			m_ID;

    const size_t	m_BufferCapacity;
    size_t			m_CurrentBufferIndex;

    VertexBuffer(const size_t size) :
            m_BufferCapacity(size),
            m_CurrentBufferIndex(0)
    {
        glGenBuffers(1, &this->m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);

        glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGetLastError();
    }

    ~VertexBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &this->m_ID);

        glGetLastError();
    }

    inline void Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
    }

    inline void Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	size_t BufferVertexData(const void* data, size_t size)
    ///
    /// Summary:	Stores new data in vertex buffer and returns an index to first data location in buffer.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	7/10/2017
    ///
    /// Parameters:
    /// data - 	   	The data.
    /// size - 	   	The size.
    ///
    /// Returns:	A size_t.
    ///-------------------------------------------------------------------------------------------------

    size_t BufferVertexData(const void* data, size_t size)
    {
        CNC_ASSERT(this->m_CurrentBufferIndex + size < this->m_BufferCapacity && "VertexBuffer capacity exceeded.");

        size_t dataBufferIndex = this->m_CurrentBufferIndex;

        glBufferSubData(GL_ARRAY_BUFFER, this->m_CurrentBufferIndex, size, data);
        glGetLastError();

        this->m_CurrentBufferIndex += size;

        return dataBufferIndex;
    }
};

struct IndexBuffer {

    GLuint			m_ID;

    const size_t	m_BufferCapacity;
    size_t			m_CurrentBufferIndex;

    IndexBuffer(const size_t size) :
            m_BufferCapacity(size),
            m_CurrentBufferIndex(0)
    {
        glGenBuffers(1, &this->m_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGetLastError();
    }

    ~IndexBuffer()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &this->m_ID);

        glGetLastError();
    }

    inline void Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);
    }

    inline void Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	size_t BufferIndexData(const void* data, size_t size)
    ///
    /// Summary:	Stores new index data in index buffer and returns an index to first data location in buffer.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	7/10/2017
    ///
    /// Parameters:
    /// data - 	   	The data.
    /// size - 	   	The size.
    ///
    /// Returns:	A size_t.
    ///-------------------------------------------------------------------------------------------------

    size_t BufferIndexData(const void* data, size_t size)
    {
        CNC_ASSERT(this->m_CurrentBufferIndex + size < this->m_BufferCapacity && "IndexBuffer capacity exceeded.");

        size_t dataBufferIndex = this->m_CurrentBufferIndex;

        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, this->m_CurrentBufferIndex, size, data);
        glGetLastError();

        this->m_CurrentBufferIndex += size;

        return dataBufferIndex;
    }
};

};

#endif // CONCUSSION_GLBUFFER_HH
