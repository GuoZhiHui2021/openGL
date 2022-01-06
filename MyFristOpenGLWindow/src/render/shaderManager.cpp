#include "shaderManager.h"
#include "vertexShader.h"
#include "fragmentShader.h"
#include "def.h"
#include <iostream>
using namespace _Shader;

_Shader::ShaderManager::~ShaderManager()
{
	if (!m_initialized)
		return;
	for (auto it : m_shaderMap)
	{
		unsigned int shaderType = it.first;
		unordered_map<string, Shader*> shaderMap = it.second;
		ShaderFactory* shaderFactory = nullptr; 
		if(m_shaderFactoryMap.find(shaderType)!= m_shaderFactoryMap.end())
			shaderFactory = m_shaderFactoryMap.at(shaderType);
		auto itShader = shaderMap.begin();
		while (itShader!= shaderMap.end())
		{
			Shader* shader = itShader->second;
			shaderMap.erase(itShader++);
			if (shaderFactory)
				shaderFactory->destoryShader(shader);
			else
			{
				shader->deleteShader();
				delete shader;
			}
		}
	}
}
void _Shader::ShaderManager::initialize()
{
	if (m_initialized)
		return;
	//m_shaderMap.clear();
	//m_shaderFactoryMap.clear();
	//m_shaderMap = unordered_map<unsigned int, unordered_map<string, Shader*>>();
	//m_shaderFactoryMap = unordered_map<unsigned int, ShaderFactory*>();
	for (auto shaderType : SHADER_TYPES)
	{
		m_shaderMap.insert(std::make_pair(shaderType, unordered_map<string, Shader*>()));
	}
	m_shaderFactoryMap.insert(std::make_pair(GL_VERTEX_SHADER, new TplShaderFactory<VertexShader>()));
	m_shaderFactoryMap.insert(std::make_pair(GL_FRAGMENT_SHADER, new TplShaderFactory<FragmentShader>()));
	m_initialized = true;
}

bool _Shader::ShaderManager::addShader(unsigned int ShaderType, const string & name)
{
	auto it = m_shaderMap.find(ShaderType);
	auto itFactory = m_shaderFactoryMap.find(ShaderType);
	if (itFactory == m_shaderFactoryMap.end()|| it == m_shaderMap.end())
	{
		std::cout << "ERROR::SHADER::ADD_SHADER_FAILED\n" << name <<std::endl;
		return false;
	}
	if (it->second.find(name) != it->second.end())
	{
		std::cout << "ERROR::SHADER::ADD_SHADER_REPEAT\n" << name << std::endl;
		return false;
	}
	Shader* shader = itFactory->second->createShader(name);
	if (!shader)
	{
		std::cout << "ERROR::SHADER::CREATE_SHADER_FAILED\n" << name << std::endl;
		return false;
	}
	it->second.insert(std::make_pair(name, shader));
	return true;
}

Shader * _Shader::ShaderManager::getShader(unsigned int ShaderType, const string & name)
{
	auto iter = m_shaderMap.find(ShaderType);
	if (iter == m_shaderMap.end())
	{
		std::cout << "ERROR::SHADER::NOT_SHADER_MAP_TYPE\n" << ShaderType << std::endl;
		return nullptr;
	}
	auto shaderIter = iter->second.find(name);
	if (shaderIter == iter->second.end())
	{
		Shader* shader = m_shaderFactoryMap.find(ShaderType)->second->createShader(name);
		if (shader)
		{
			iter->second.insert(std::make_pair(name, shader));
			return shader;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return shaderIter->second;
	}

}


