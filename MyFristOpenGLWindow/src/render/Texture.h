#pragma once
#include <string>
#include <GLFW/glfw3.h>
class Texture
{
public:
	Texture():m_texture(0), m_name(""),m_width(0), m_height(0), m_nrChannels(0)
	{}
	bool load(const char * src);
	void use(uint16_t textureUnit,uint16_t parameter[]);
	unsigned int getTextureID() {return m_texture; }
	const std::string& getName() { return m_name; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	int getChannelSize() { return m_nrChannels; }
private:
	unsigned int m_texture;
	std::string m_name;
	int m_width; 
	int m_height;
	int	m_nrChannels;
};

