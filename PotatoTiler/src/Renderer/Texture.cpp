#include "Texture.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

Texture::Texture(const char* path)
{
	stbi_set_flip_vertically_on_load(true);

	unsigned char* texBuffer = stbi_load(path, &m_Width, &m_Height, &m_BPP, 4);
	glGenTextures(1, &m_TexID);
	glBindTexture(GL_TEXTURE_2D, m_TexID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texBuffer);

	if (texBuffer) stbi_image_free(texBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TexID);
}

void Texture::bind(unsigned short slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
