#include <PrecompiledHeader.h>
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace GameWorld
{
	static void CheckChannels(GW_INT32 channels_, GLenum& internal_format, GLenum& data_format)
	{
		switch (channels_)
		{
		case 4:
		{
			internal_format = GL_RGBA8;
			data_format = GL_RGBA;
			break;
		}
		case 3:
		{
			internal_format = GL_RGB8;
			data_format = GL_RGB;
			break;
		}
		case 1:
		{
			internal_format = GL_R8;
			data_format = GL_RED;
			break;
		}
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string path)
		: texture_path_(path)
	{
		stbi_set_flip_vertically_on_load(1);

		GW_UINT8* data  = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);
		
		GLenum internal_format = 0 , data_format = 0;

		if (data)
		{
			CheckChannels(channels_, internal_format, data_format);

			glCreateTextures(GL_TEXTURE_2D , 1, &texture_id_);
			glTextureStorage2D(texture_id_, 1, internal_format, width_, height_);

			glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(texture_id_, 0, 0, 0, width_, height_, data_format, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			GAMEWORLD_CORE_ERROR("Failed to load Texture![Path:{0}]", path);
		}
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &texture_id_);
	}



	void OpenGLTexture2D::Attach(GW_UINT32 slot) const
	{
		glBindTextureUnit(slot, texture_id_);
	}


	OpenGLTextureCube3D::OpenGLTextureCube3D(const std::array<TextureInfo, 6>& faces)
		: width_(faces[0].width), height_(faces[0].height)
	{
		stbi_set_flip_vertically_on_load(0);

		glGenTextures(1, &texture_id_);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);

		for (GW_UINT32 i = 0; i < faces.size(); i++)
		{
			//GW_UINT8 *data = stbi_load(faces[i].c_str(), &width_, &height_, &channels_, 0);
			if (faces[i].data)
			{
				GLenum internal_format = 0, data_format = 0;
				CheckChannels(faces[i].channels, internal_format, data_format);
				
				glTexImage2D(
						GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
						internal_format, faces[i].width, faces[i].height, 0, data_format, GL_UNSIGNED_BYTE, faces[i].data);
				glGenerateMipmap(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			}
			//stbi_image_free(data);
		}
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLTextureCube3D::~OpenGLTextureCube3D()
	{
		glDeleteTextures(1, &texture_id_);
	}

	void OpenGLTextureCube3D::Attach(GW_UINT32 slot /*= 0*/) const
	{
		glBindTextureUnit(slot, texture_id_);
	}

}