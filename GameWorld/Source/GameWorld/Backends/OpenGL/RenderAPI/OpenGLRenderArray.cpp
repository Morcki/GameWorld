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
		glGenVertexArrays(1, &RenderArrayID);
	}

	OpenGLRenderArray::~OpenGLRenderArray()
	{
		glDeleteVertexArrays(1, &RenderArrayID);
	}

	void OpenGLRenderArray::Bind() const
	{
		glBindVertexArray(RenderArrayID);
	}

	void OpenGLRenderArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLRenderArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		RenderBufferLayout& layout = vertexBuffer->GetLayout();
		GAMEWORLD_CORE_ASSERT(layout.GetElements().size(), "Vertex Buffer Layout is Empty!");

		glBindVertexArray(RenderArrayID);
		vertexBuffer->Bind();

		

		GW_UINT32 index = 0;
		for (RenderBufferElement& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.Count,
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(void*)element.Offset);
			++index;
		}

		VertexBufferVector.push_back(vertexBuffer);
	}

	void OpenGLRenderArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(RenderArrayID);
		indexBuffer->Bind();

		IndexBufferSingle = indexBuffer;
	}

}