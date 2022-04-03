#include <PrecompiledHeader.h>
#include "GImage.h"

#include "stb_image.h"

namespace GameWorld
{
	GImage::GImage(const std::string& image_file, GW_BOOL bflip)
	{
		Load(image_file, bflip);
	}

	GImage::GImage(const std::string& image_file, const std::string& directory, GW_BOOL bflip /*= true*/)
	{
		Load(directory + '/' + image_file, bflip);
	}

	GImage::~GImage()
	{
		data ? stbi_image_free(data) : free(data);
	}

	GW_BOOL GImage::Load(const std::string& image_file, GW_BOOL bflip)
	{
		if (image_file.empty()) return false;
		Free();

		image_path_ = image_file;
		stbi_set_flip_vertically_on_load(bflip);
		data = stbi_load(image_file.c_str(), &width, &height, &channels, 0);

		if (!data)
		{
			GAMEWORLD_CORE_ERROR("Failed to load image file : {0}", image_file);
			return false;
		}
		return true;
	}

	void GImage::Swap(GImage& image) noexcept
	{
		GImage::Swap(std::move(image));
	}

	void GImage::Swap(GImage&& image) noexcept
	{
		if (this == &image) return;
		using std::swap;

		auto ptr_image = &image;
		swap(this->width, ptr_image->width);
		swap(this->height, ptr_image->height);
		swap(this->channels, ptr_image->channels);
		swap(this->image_path_, ptr_image->image_path_);
		swap(this->data, ptr_image->data);
	}

	GW_BOOL GImage::Free()
	{
		if (data)
		{
			stbi_image_free(data);
			data = nullptr;
			return true;
		}
		return false;
	}

	GW_BOOL GImage::IsEmpty()
	{
		return data == nullptr;
	}

}