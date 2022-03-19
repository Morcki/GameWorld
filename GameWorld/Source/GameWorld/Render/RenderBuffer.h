#pragma once
#include "ShaderTool.h"

namespace GameWorld
{
	struct RenderBufferElement
	{
		std::string Name;
		ShaderDataType Type;
		GW_UINT32 Size;
		GW_UINT32 Count;
		size_t Offset;
		GW_BOOL Normalized;

		RenderBufferElement() = default;

		RenderBufferElement(ShaderDataType type, const std::string& name, GW_BOOL normalized = false) : 
			Name(name), 
			Type(type), 
			Size(ShaderTool::ShaderDataTypeSize(type)),
			Count(ShaderTool::ShaderDataTypeCount(type)),
			Offset(0),
			Normalized(normalized)
		{}

	};

	class RenderBufferLayout
	{
	public:
		RenderBufferLayout() {}

		RenderBufferLayout(std::initializer_list<RenderBufferElement> elements)
			: BufferElements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return StrideLength; }
		
		const std::vector<RenderBufferElement>& GetElements() const { return BufferElements; }

		std::vector<RenderBufferElement>::iterator begin()             { return BufferElements.begin(); }
		std::vector<RenderBufferElement>::iterator end()               { return BufferElements.end(); }
		std::vector<RenderBufferElement>::const_iterator begin() const { return BufferElements.begin(); }
		std::vector<RenderBufferElement>::const_iterator end()   const { return BufferElements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			StrideLength = 0;
			for (auto& element : BufferElements)
			{
				element.Offset = offset;
				offset += element.Size;
				StrideLength += element.Size;
			}
		}
	private:
		std::vector<RenderBufferElement> BufferElements;
		uint32_t StrideLength = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		inline void SetLayout(RenderBufferLayout bufferLayout) { BufferLayout = bufferLayout; };
		inline RenderBufferLayout& GetLayout() { return BufferLayout; };

		static VertexBuffer* CreateVertexBuffer(GW_FLOAT32* buff, GW_UINT32 size);

	private:
		RenderBufferLayout BufferLayout;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual GW_UINT32 Count() const = 0;

		static IndexBuffer* CreateIndexBuffer(GW_UINT32* buff, GW_UINT32 count);
	};
}