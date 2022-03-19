#pragma once

#include "GameWorld/Render/RenderBuffer.h"

namespace GameWorld
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(GW_FLOAT32* vertices, GW_UINT32 size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind()   const override;
		virtual void UnBind() const override;

	private:
		GW_UINT32 BufferID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(GW_UINT32* indices, GW_UINT32 count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind()   const override;
		virtual void UnBind() const override;

		virtual GW_UINT32 Count() const override { return IndexSize; };

	private:
		GW_UINT32 BufferID;
		GW_UINT32 IndexSize;
	};

}
