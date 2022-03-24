#pragma once
#include "ShaderTool.h"

namespace GameWorld
{
	struct RenderBufferElement
	{
		std::string name;
		ShaderDataType type;
		GW_UINT32 size;
		GW_UINT32 count;
		size_t offset;
		GW_BOOL normalized;

		RenderBufferElement() = default;

		RenderBufferElement(ShaderDataType type_in, const std::string& name_in, GW_BOOL normalized_in = false) : 
			name(name_in), 
			type(type_in), 
			size(ShaderTool::ShaderDataTypeSize(type)),
			count(ShaderTool::ShaderDataTypeCount(type)),
			offset(0),
			normalized(normalized_in)
		{}

	};

	class RenderBufferLayout
	{
	public:
		RenderBufferLayout() {}

		RenderBufferLayout(std::initializer_list<RenderBufferElement> elements)
			: buffer_elements_(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return stride_length_; }
		
		const std::vector<RenderBufferElement>& GetElements() const { return buffer_elements_; }

		std::vector<RenderBufferElement>::iterator begin()             { return buffer_elements_.begin(); }
		std::vector<RenderBufferElement>::iterator end()               { return buffer_elements_.end(); }
		std::vector<RenderBufferElement>::const_iterator begin() const { return buffer_elements_.begin(); }
		std::vector<RenderBufferElement>::const_iterator end()   const { return buffer_elements_.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			stride_length_ = 0;
			for (auto& element : buffer_elements_)
			{
				element.offset = offset;
				offset += element.size;
				stride_length_ += element.size;
			}
		}
	private:
		std::vector<RenderBufferElement> buffer_elements_;
		uint32_t stride_length_ = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		inline void SetLayout(RenderBufferLayout buffer_layout) { buffer_layout_ = buffer_layout; };
		inline RenderBufferLayout& GetLayout() { return buffer_layout_; };

		static Ref<VertexBuffer> CreateVertexBuffer(GW_FLOAT32* buff, GW_UINT32 size);

	private:
		RenderBufferLayout buffer_layout_;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual GW_UINT32 Count() const = 0;

		static Ref<IndexBuffer> CreateIndexBuffer(GW_UINT32* buff, GW_UINT32 count);
	};
}