#pragma once

#include <string>

namespace GameWorld
{
	class GImage
	{
	public:
		GImage() {};
		GImage(const std::string& image_file, GW_BOOL bflip = true);
		~GImage();

		GW_BOOL LoadFromFile(const std::string& image_file, GW_BOOL bflip = true);
		GW_BOOL FreeImageData();

	public:
		GW_BOOL IsEmptyImage();
		const GW_UINT8* operator*() const { return data; };
		const GW_UINT8* GetData() const { return data; };

	public:
		GW_INT32  width{ 0 };
		GW_INT32  height{ 0 };
		GW_INT32  channels{ 0 };
	private:
		GW_UINT8* data{ nullptr };
	};
}