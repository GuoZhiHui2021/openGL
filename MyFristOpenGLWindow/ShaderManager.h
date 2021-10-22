#pragma once
#include "Shader.h"
#include "Singleton.h"
#include "ShaderFactory.h"
#include <string>
#include <unordered_map>
namespace _Shader
{
	using std::string;
	using std::unordered_map;
	class ShaderManager:public Singleton<ShaderManager>
	{
	public:
		ShaderManager() :m_initialized(false){ }
		~ShaderManager();
		void initialize();
		bool addShader(unsigned int ShaderType,const string& name);
		Shader* getShader(unsigned int ShaderType, const string& name);
	public:
		unordered_map<unsigned int,unordered_map<string, Shader*>> m_shaderMap;
		unordered_map<unsigned int, ShaderFactory*> m_shaderFactoryMap;
		bool m_initialized;
	};
}


