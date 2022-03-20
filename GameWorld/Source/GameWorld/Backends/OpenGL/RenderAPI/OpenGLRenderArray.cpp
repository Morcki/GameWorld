#include <PrecompiledHeader.h>

#include "OpenGLRenderArray.h"

#include "glad/glad.h"

namespace GameWorld
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		GAMEWORLD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	};

	OpenGLRenderArray::OpenGLRenderArray()
	{
		glGenVertexArrays(1, &render_array_id_);
	}

	OpenGLRenderArray::~OpenGLRenderArray()
	{
		glDeleteVertexArrays(1, &render_array_id_);
	}

	void OpenGLRenderArray::Bind() const
	{
		glBindVertexArray(render_array_id_);
	}

	void OpenGLRenderArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLRenderArray::AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer)
	{
		RenderBufferLayout& layout = vertex_buffer->GetLayout();
		GAMEWORLD_CORE_ASSERT(layout.GetElements().size(), "Vertex Buffer Layout is Empty!");

		glBindVertexArray(render_array_id_);
		vertex_buffer->Bind();

		

		GW_UINT32 index = 0;
		for (RenderBufferElement& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.count,
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(void*)element.offset);
			++index;
		}

		vertex_buffer_vec_.push_back(vertex_buffer);
	}

	void OpenGLRenderArray::SetIndexBuffer(const Ref<IndexBuffer>& index_buffer)
	{
		glBindVertexArray(render_array_id_);
		index_buffer->Bind();

		index_buffer_ = index_buffer;
	}

}