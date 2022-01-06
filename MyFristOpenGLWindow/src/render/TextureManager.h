#pragma once
#include "common/singleton.h"
#include "texture.h"
#include <unordered_map>
#include <string>
class TextureManager:public Singleton<TextureManager>
{
	
public:
	TextureManager();
	Texture* getOrCreateTexture(std::string src);
	unsigned short getOption(std::string name)
	{
		if (m_optionTypeMap.find(name) == m_optionTypeMap.end())
			return 0;
		return m_optionTypeMap[name];
	}
private:
	std::unordered_map<std::string, Texture*> m_textures;
	std::unordered_map<std::string, unsigned short> m_optionTypeMap;
};

