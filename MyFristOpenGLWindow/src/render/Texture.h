#pragma once
#include <string>
#include <GLFW/glfw3.h>
class Texture
{
public:
	Texture(unsigned int min_minmap = 0,unsigned int weap_s = GL_REPEAT, unsigned int weap_t = GL_REPEAT, unsigned int min_filter = GL_NEAREST, unsigned int mag_filter = GL_NEAREST):m_id(0), m_name(""), \
		m_width(0), m_height(0), m_nrChannels(0),MIN_FILTER(min_filter),MAG_FILTER(mag_filter), WRAP_S(weap_s), WRAP_T(weap_t)
	{}
	bool load(const char * src);
private:
	unsigned int m_id;
	unsigned int MIN_FILTER;
	unsigned int MAG_FILTER;
	unsigned int MIN_MINMAP;
	unsigned int WRAP_S;
	unsigned int WRAP_T;
	std::string m_name;
	int m_width; 
	int m_height;
	int	m_nrChannels;
};

