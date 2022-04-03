#pragma once

#include <string>

namespace GameWorld
{
	class GImage
	{
	public:
		GImage() {};
		GImage(const std::string& image_file, GW_BOOL bflip = true);
		GImage(const std::string& image_file, const std::string& directory, GW_BOOL bflip = true);
		~GImage();

	public: /* copy and move constructor */
		GImage(GImage& obj)
		{
			GImage::Swap(obj);
		}

		GImage& operator=(GImage& obj)
		{
			GImage::Swap(obj);
			return *this;
		}

		GImage(GImage&& obj)
		{
			GImage::Swap(obj);
		}

		GImage& operator=(GImage&& obj)
		{
			GImage::Swap(obj);
			return *this;
		}

		GW_BOOL Load(const std::string& image_file, GW_BOOL bflip = true);
		void    Swap(GImage& image)  noexcept;
		void    Swap(GImage&& image) noexcept;
		GW_BOOL Free();

	public:
		GW_BOOL IsEmpty();
		const std::string& GetImagePath() const { return image_path_; };
		const GW_UINT8* operator*() const { return data; };
		const GW_UINT8* GetData() const { return data; };

	public:
		GW_INT32  width{ 0 };
		GW_INT32  height{ 0 };
		GW_INT32  channels{ 0 };
	private:
		std::string image_path_;
		GW_UINT8* data{ nullptr };
	};
}