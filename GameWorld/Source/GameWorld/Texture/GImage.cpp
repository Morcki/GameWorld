#include <PrecompiledHeader.h>
#include "GImage.h"

#include "stb_image.h"

namespace GameWorld
{
	GImage::GImage(const std::string& image_file, GW_BOOL bflip)
	{
		LoadFromFile(image_file, bflip);
	}

	GImage::~GImage()
	{
		data ? stbi_image_free(data) : free(data);
	}

	GW_BOOL GImage::LoadFromFile(const std::string& image_file, GW_BOOL bflip)
	{
		if (image_file.empty()) return false;
		FreeImageData();

		stbi_set_flip_vertically_on_load(bflip);
		data = stbi_load(image_file.c_str(), &width, &height, &channels, 0);

		if (!data)
		{
			GAMEWORLD_CORE_ERROR("Failed to load image file : {0}", image_file);
			return false;
		}
		return true;
	}

	GW_BOOL GImage::FreeImageData()
	{
		if (data)
		{
			stbi_image_free(data);
			data = nullptr;
			return true;
		}
		return false;
	}

	GW_BOOL GImage::IsEmptyImage()
	{
		return data == nullptr;
	}

}