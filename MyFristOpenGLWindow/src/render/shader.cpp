#include "shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
using namespace _Shader;
Shader::Shader(const GLchar * shaderSource, unsigned int shaderType)
{
	m_compile = false;
	m_shaderID = 0,
	m_shaderCode = NULL; 
	m_shader = "";
	load(shaderSource, shaderType);
}

Shader::~Shader()
{
	if (m_shaderCode)
	{
		delete m_shaderCode;
	}
}

void Shader::load(const GLchar * shaderSource, unsigned int shaderType)
{
	deleteShader();
	try
	{
		m_shaderID = glCreateShader(shaderType);
		std::ifstream shaderFile;
		shaderFile.open(shaderSource);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		std::string str = shaderStream.str();
		auto c_str = str.c_str();
		m_shaderCode = (char*)malloc(str.size() + 1);
		auto c = str.size();
		if (m_shaderCode)
		{
			strcpy_s(m_shaderCode, str.size() + 1, c_str);
		}
		m_shader = const_cast<GLchar*>(shaderSource);
		shaderFile.close();
		printf("-----------------------------------\nload shader succ:\nname:%s\ncode:\n%s\n-----------------------------------\n\n\n\n\n", shaderSource,m_shaderCode);
	}
	catch (const std::exception&)
	{
		deleteShader();
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

unsigned int Shader::getShaderID()
{
	return m_shaderID;
}

const GLchar * Shader::getShaderCode()
{
	return m_shaderCode;
}

void Shader::deleteShader()
{
	if (m_shaderID)
	{
		glDeleteShader(m_shaderID);
		m_compile = false;
		m_shaderID = 0;
		if (m_shaderCode)
		{
			free(m_shaderCode);
		}
		m_shaderCode = NULL;
		m_shader.clear();
	}
}

bool Shader::compile()
{
	if (m_compile)
		return true;
	unsigned int shaderID = getShaderID();
	const GLchar * shaderCode = getShaderCode();
	glShaderSource(shaderID, 1, &shaderCode ,NULL);
	glCompileShader(shaderID);
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
	}
	m_compile = true;
	return success;
}
