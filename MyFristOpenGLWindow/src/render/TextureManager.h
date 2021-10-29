#pragma once
#include "common/Singleton.h"
#include "Texture.h"
#include <unordered_map>
#include <string>
class TextureManager:public Singleton<TextureManager>
{
	
public:
	Texture* getOrCreateTexture(std::string src);
private:
	std::unordered_map<std::string, Texture*> m_textures;
};

