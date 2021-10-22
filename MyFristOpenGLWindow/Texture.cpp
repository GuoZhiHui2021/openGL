#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
bool Texture::load(const char * src)
{
	/*int width, height, nrChannels;
	unsigned char *data = stbi_load(src, &width, &height, &nrChannels, 0);
	if(!data)
		return false;
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T);
	if (MIN_MINMAP)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_MINMAP);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	m_width = width;
	m_height = height;
	m_nrChannels = nrChannels;
	m_name.replace(m_name.begin(), m_name.end(), src);
	return true;*/
	return false;
}
