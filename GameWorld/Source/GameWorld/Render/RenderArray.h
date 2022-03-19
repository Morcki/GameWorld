#pragma once

#include "GameWorld/Render/RenderBuffer.h"

namespace GameWorld
{
	class RenderArray
	{
	public:
		virtual ~RenderArray() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>&) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>&) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static RenderArray* CreateRenderArray();
	};

}
