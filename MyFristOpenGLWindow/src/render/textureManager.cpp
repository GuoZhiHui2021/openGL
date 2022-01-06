#include "TextureManager.h"
#include <common/util.h>
#include <algorithm>

TextureManager::TextureManager()
{
	m_optionTypeMap.insert(std::make_pair("REPEAT", GL_REPEAT));
	m_optionTypeMap.insert(std::make_pair("NEAREST", GL_NEAREST));
}

Texture * TextureManager::getOrCreateTexture(std::string src)
{
	if (m_textures.find(src) != m_textures.end())
	{
		return m_textures[src];
	}
	Texture* new_tex = new Texture();
	const char * name = src.c_str();
	unsigned int hex = 0;
	if (strToRGBA(src.c_str(), hex))
	{
		unsigned char a = hex & 0xFF;
		unsigned char b = (hex>>8) & 0xFF;
		unsigned char g = (hex>>16) & 0xFF;
		unsigned char r = (hex>>24) & 0xFF;
		if (new_tex->load(r, g, b, a))
		{
			std::transform(src.begin(), src.end(), src.begin(), ::toupper);
			m_textures[src] = new_tex;
			return new_tex;
		}
		else
		{
			delete new_tex;
		}
	}
	else if (new_tex->load(name))
	{
		m_textures[src] = new_tex;
		return new_tex;
	}
	else
	{
		delete new_tex;
	}
	return nullptr;
}
