#include<glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "common/FileUtil.h"
bool Texture::load(const char * src)
{
	if (m_texture)
	{
		return false;
	}
	int width, height, nrChannels;
	std::string path = getAbsolutePath(src);
	stbi_set_flip_vertically_on_load(false);
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if(!data)
		return false;
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (nrChannels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else if (nrChannels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		_ASSERT_EXPR(false, "Texture Error!");
	
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	m_width = width;
	m_height = height;
	m_nrChannels = nrChannels;
	m_name.replace(m_name.begin(), m_name.end(), src);
	m_texture = texture;
	return true;
}

bool Texture::load(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	if (m_texture)
	{
		return false;
	}
	m_nrChannels = 4;
	m_width = 1;
	m_height = 1;
	unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	if (!data)
		return false;
	data[0] = r < 0 ? 0 : r>255 ? 255 : r;
	data[1] = g < 0 ? 0 : g>255 ? 255 : g;
	data[2] = b < 0 ? 0 : b>255 ? 255 : b;
	data[3] = a < 0 ? 0 : a>255 ? 255 : a;
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	char src[11];
	sprintf_s(src, "%#X%X%X%X", r, g, b, a);
	src[10] = '\0';
	m_name.replace(m_name.begin(), m_name.end(), src);
	m_texture = texture;
	return true;
}

void Texture::use(uint16_t textureUnit,uint16_t parameter[])
{
	if (!m_texture) return;
	uint16_t wrap_s = parameter[0];
	uint16_t wrap_t = parameter[1];
	uint16_t min_filter = parameter[2];
	uint16_t max_filter = parameter[3];
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, max_filter);

}

