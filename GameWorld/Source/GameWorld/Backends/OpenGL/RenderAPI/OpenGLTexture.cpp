#include <PrecompiledHeader.h>
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace GameWorld
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string path)
		: texture_path_(path)
	{
		stbi_set_flip_vertically_on_load(1);

		GW_UINT8* data  = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);

		if (data)
		{
			glCreateTextures(GL_TEXTURE_2D , 1, &texture_id_);
			glTextureStorage2D(texture_id_, 1, GL_RGB8, width_, height_);

			glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(texture_id_, 0, 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			texture_id_ = 0;
			GAMEWORLD_CORE_ERROR("Failed to load Texture![{0}]", path);
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

}