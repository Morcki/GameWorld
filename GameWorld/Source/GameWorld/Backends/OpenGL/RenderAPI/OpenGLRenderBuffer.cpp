#include <PrecompiledHeader.h>
#include "OpenGLRenderBuffer.h"

#include "glad/glad.h"

namespace GameWorld
{

	///////////////////////////
	////OpenGL VertexBuffer////
	///////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(GW_FLOAT32* vertices, GW_UINT32 size)
	{
		glGenBuffers(1, &buffer_id_);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &buffer_id_);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	///////////////////////////
	////OpenGL IndexBuffer////
	///////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(GW_UINT32* indices, GW_UINT32 count)
		: index_size_(count)
	{
		glGenBuffers(1, &buffer_id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GW_UINT32), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &buffer_id_);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}