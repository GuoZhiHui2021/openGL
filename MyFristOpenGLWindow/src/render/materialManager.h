#pragma once
#include <unordered_map>
#include <string>
#include <common/singleton.h>
#include "material.h"
class MaterialManager:public Singleton<MaterialManager>
{
public:
	MaterialManager();
	MaterialPrototype* getOrCreateMaterialPrototype(std::string name);
	Material* getOrCreateMaterial(std::string name);
	void* deserialization(uint16_t type, std::string src);
	size_t getDataSize(uint16_t type);
	bool isShaderType(unsigned short type)
	{
		for (auto shaderType : m_shaderTypeMap)
		{
			if (shaderType.second == type)
				return true;
		}
		return false;
	}
	template<uint16_t T>
	void* deserialization(std::string src);

	template<>
	void* deserialization<GL_INT>(std::string src);

	template<>
	void* deserialization<GL_FLOAT>(std::string src);

	template<>
	void* deserialization<GL_FLOAT_VEC2>(std::string src); 

	template<>
	void* deserialization<GL_FLOAT_VEC3>(std::string src);

	template<>
	void* deserialization<GL_FLOAT_VEC4>(std::string src);

	
private:
	std::unordered_map<std::string, MaterialPrototype*> m_materialPrototypes;
	std::unordered_map<std::string, Material*> m_materials;
	std::unordered_map<std::string, unsigned short> m_shaderTypeMap;
	std::unordered_map<std::string, unsigned short> m_AttrTypeMap;
};


