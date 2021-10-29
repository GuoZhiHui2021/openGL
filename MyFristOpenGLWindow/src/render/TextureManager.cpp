#include "TextureManager.h"

Texture * TextureManager::getOrCreateTexture(std::string src)
{
	if (m_textures.find(src) != m_textures.end())
	{
		return m_textures[src];
	}
	Texture* new_tex = new Texture();
	const char * name = src.c_str();
	if (new_tex->load(name))
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
