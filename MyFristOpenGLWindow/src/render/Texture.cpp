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
	stbi_set_flip_vertically_on_load(true);
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

