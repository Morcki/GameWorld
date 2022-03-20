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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& index_buffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override { return vertex_buffer_vec_; };
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return index_buffer_; };

	private:
		GW_UINT32 render_array_id_;
		std::vector<Ref<VertexBuffer>> vertex_buffer_vec_;
		Ref<IndexBuffer> index_buffer_;
	};

}
