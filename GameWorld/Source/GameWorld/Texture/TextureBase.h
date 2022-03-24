#pragma once

#include <string>

#include "GameWorld/Core/Core.h"

namespace GameWorld
{
	class TextureBase
	{
	public:
		virtual ~TextureBase() = default;

		virtual GW_INT32 GetWidth()  const = 0;
		virtual GW_INT32 GetHeight() const = 0;

		virtual void Attach(GW_UINT32 slot = 0) const = 0;

	};

	class Texture2D : public TextureBase
	{
	public:
		static Ref<Texture2D> CreateTexture2D(const std::string& path);
	};
}