#include "gppch.h"
#include "Texture.h"

#include "../vendor/stb_image/stb_image.h"

#include <glad/glad.h>
namespace Graphite {
	Texture::Texture(const char* textPath)
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width = 0;
		int height = 0;
		int nrChannels = 0;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(textPath, &width, &height, &nrChannels, 0);
		if (data)
		{
			//GP_CORE_INFO("width: {0}: ", width);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			GP_CORE_ERROR("FAILED TO LOAD TEXTURE");
		}	
		stbi_image_free(data);
	}
	Texture::Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	uint32_t Texture::getID()
	{
		return m_RendererID;
	}
}