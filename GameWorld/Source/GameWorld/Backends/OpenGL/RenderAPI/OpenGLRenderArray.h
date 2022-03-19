#pragma once

#include "GameWorld/Render/RenderArray.h"

namespace GameWorld
{
	class OpenGLRenderArray : public RenderArray
	{
	public:
		OpenGLRenderArray();
		virtual ~OpenGLRenderArray();

		virtual void Bind()   const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override { return VertexBufferVector; };
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return IndexBufferSingle; };

	private:
		GW_UINT32 RenderArrayID;
		std::vector<Ref<VertexBuffer>> VertexBufferVector;
		Ref<IndexBuffer> IndexBufferSingle;
	};

}
