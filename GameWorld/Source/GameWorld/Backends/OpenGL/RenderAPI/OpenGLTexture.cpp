#include <PrecompiledHeader.h>
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace GameWorld
{
	static void CheckChannels(GW_INT32 channels_, GW_BOOL bgama, GLenum& internal_format, GLenum& data_format)
	{
		switch (channels_)
		{
		case 4:
			internal_format = bgama ? GL_SRGB8 : GL_RGBA8;
			data_format = GL_RGBA;
			break;
		case 3:
			internal_format = bgama ? GL_SRGB8 : GL_RGB8;
			data_format = GL_RGB;
			break;
		case 1:
			internal_format = GL_RED;
			data_format = GL_RED;
			break;
		}
	}

	static GLenum TextureTypeToOpenGL(ETextureType type)
	{
		switch (type)
		{
		case ETextureType::kInValid:
			return 0;
		case ETextureType::kTexture2D:
			return GL_TEXTURE_2D;
		case ETextureType::kCubeMap:
			return GL_TEXTURE_CUBE_MAP;
		default:
			return 0;
		}
	}
	
	OpenGLTexture::OpenGLTexture(const std::string path, GW_BOOL bflip /*= true*/, GW_BOOL bgama /*= false*/)
	{
		GImage image(path, bflip);
		LoadImage(image, bgama);
	}

	OpenGLTexture::OpenGLTexture(const GImage& image, GW_BOOL bgama /*= false*/)
	{
		LoadImage(image, bgama);
	}

	OpenGLTexture::OpenGLTexture(const std::array<std::string, 6> skybox_files, GW_BOOL bflip /*= true*/, GW_BOOL bgama /*= false*/)
	{
		std::array<GImage, 6> skybox_images;
		for (GW_INT32 i = 0; i < 6; i++)
		{
			skybox_images[i].LoadFromFile(skybox_files[i], bflip);
		}
		LoadSkybox(skybox_images, bgama);
	}

	OpenGLTexture::OpenGLTexture(const std::array<GImage, 6>& skybox_images, GW_BOOL bgama /*= false*/)
	{
		LoadSkybox(skybox_images, bgama);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &texture_id_);
	}

	void OpenGLTexture::Bind(GW_UINT32 slot /*= ETextureType::kTex2D*/) const
	{
		if (IsValid())
		{
			glBindTextureUnit(slot, texture_id_);
		}
	}

	void OpenGLTexture::UnBind(GW_UINT32 slot /*= ETextureType::kTex2D*/) const
	{
		if (IsValid())
		{
			glBindTextureUnit(slot, 0);
		}
	}

	void OpenGLTexture::DynamicLoadImage(const GImage& image, GW_BOOL bgama)
	{
		LoadImage(image, bgama);
	}

	void OpenGLTexture::DynamicLoadSkybox(const std::array<GImage, 6>& skybox_images, GW_BOOL bgama)
	{
		LoadSkybox(skybox_images, bgama);
	}

	GW_BOOL OpenGLTexture::GenMipmap() 
	{
		if (!IsValid()) {
			GAMEWORLD_CORE_ERROR("OpenGLTexture::GenMipmap => Texture is invalid!");
			return false;
		}

		Bind();
		auto gl_type = TextureTypeToOpenGL(texture_type_);
		glTexParameteri(gl_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(gl_type);
		return true;
	}

	void OpenGLTexture::LoadImage(const GImage& image, GW_BOOL bgama)
	{
		GLenum internal_format = 0, data_format = 0;

		width_ = image.width;
		height_ = image.height;
		channels_ = image.channels;

		if (image.GetData())
		{
			CheckChannels(channels_, bgama, internal_format, data_format);

			glCreateTextures(GL_TEXTURE_2D, 1, &texture_id_);
			glTextureStorage2D(texture_id_, 1, internal_format, width_, height_);

			glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(texture_id_, 0, 0, 0, width_, height_, data_format, GL_UNSIGNED_BYTE, image.GetData());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			GAMEWORLD_CORE_ERROR("Texture load empty ImageData!");
		}
		texture_type_ = ETextureType::kTexture2D;
	}

	void OpenGLTexture::LoadSkybox(const std::array<GImage, 6>& skybox_images, GW_BOOL bgama)
	{
		// load a cubemap texture from 6 individual texture faces
		// order:
		// +X (right)
		// -X (left)
		// +Y (top)
		// -Y (bottom)
		// +Z (back) 
		// -Z (front)
		// -------------------------------------------------------

		glGenTextures(1, &texture_id_);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);

		width_ = skybox_images[0].width;
		height_ = skybox_images[0].height;
		channels_ = skybox_images[0].channels;

		for (GW_UINT32 i = 0; i < skybox_images.size(); i++)
		{
			//GW_UINT8 *data = stbi_load(faces[i].c_str(), &width_, &height_, &channels_, 0);
			if (skybox_images[i].GetData())
			{
				GLenum internal_format = 0, data_format = 0;
				CheckChannels(skybox_images[i].channels, bgama, internal_format, data_format);

				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
					internal_format, skybox_images[i].width, skybox_images[i].height, 0, data_format, GL_UNSIGNED_BYTE, skybox_images[i].GetData());
				glGenerateMipmap(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		texture_type_ = ETextureType::kCubeMap;
	}

}