#include "render/ShaderProgram.h"
#include <iostream>
#include <algorithm>
using namespace _Shader;
ShaderProgram::ShaderProgram()
{
	m_programID = glCreateProgram();
}

bool ShaderProgram::link()
{
	glLinkProgram(m_programID);
	int success;
	char infoLog[512];
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

void _Shader::ShaderProgram::attach(Shader * shader)
{
	if (!shader)
	{
		std::cout << "ERROR::ShaderProgram::ATTACH_SHADER_FAILED\n" << std::endl;
		return;
	}
	unsigned int shaderType = shader->getShaderType();
	auto it = m_shader_map.find(shaderType);
	if (it != m_shader_map.end())
	{
		Shader* old_shader = it->second;
		if (old_shader == shader)
		{
			std::cout << "WARNING::ShaderProgram::ATTACH_SAME_SHADER\n" << std::endl;
			return;
		}
		detch(old_shader);
		shader->compile();
		glAttachShader(m_programID, shader->getShaderID());
		m_shader_map[shaderType] = shader;
		//shader->deleteShader();
		std::cout << "INFO::ShaderProgram::ATTACH_SHADER_SUCC:" << shader->getShaderName()<<" "<< shaderType << std::endl;
		return;
	}
	shader->compile();
	glAttachShader(m_programID, shader->getShaderID());
	m_shader_map.insert(std::make_pair(shaderType, shader));
	//shader->deleteShader();
	std::cout << "INFO::ShaderProgram::ATTACH_SHADER_SUCC:" << shader->getShaderName() << " " << shaderType << std::endl;
}

void _Shader::ShaderProgram::detch(Shader * shader)
{
	glDetachShader(m_programID, shader->getShaderID());
}

void _Shader::ShaderProgram::setUniform(const std::string & name, void * value, uint8_t count, ShaderParamType pType)
{
	auto iter = m_unifroms.find(name);
	if (iter == m_unifroms.end())
	{
		Uniform* uniform = new Uniform();
		uniform->m_name = name;
		uniform->m_type = pType;
		uniform->setValue(value, count);
		uniform->setDirty();
		m_unifroms[name] = uniform;
	}
	else
	{
		Uniform* uniform = iter->second;
		_ASSERT_EXPR(uniform->m_type == pType , "Uniform Type Error!");
		uniform->setValue(value, count);
		uniform->setDirty();
	}
}

void ShaderProgram::use()
{
	glUseProgram(m_programID);
	for (auto iter = m_unifroms.begin(); iter != m_unifroms.end(); iter++)
	{
		auto name = iter->first;
		auto uniform = iter->second;
		if (uniform->m_isDirty)
		{
			int location = glGetUniformLocation(m_programID, name.c_str());
			uniform->m_location = location;
			if (location > -1)
			{
				uniform->update(this);
			}
				
		}
	}
	
}

unsigned int ShaderProgram::getProgramID() const
{
	return m_programID;
}

void _Shader::ShaderProgram::Uniform::setValue(const void * value, uint8_t count)
{
	size_t size = 0;
	size_t p_size = 0;
	switch (m_type)
	{
	case _Shader::SPT_UNKNOWN:
		break;
	case _Shader::SPT_INT:
		p_size = sizeof(int);
		size = p_size;
		break;
	case _Shader::SPT_FLOAT:
		p_size = sizeof(float);
		size = p_size;
		break;
	case _Shader::SPT_VEC2:
		p_size = sizeof(float);
		size = p_size * 2;
		break;
	case _Shader::SPT_VEC3:
		p_size = sizeof(float);
		size = p_size * 3;
		break;
	case _Shader::SPT_VEC4:
		p_size = sizeof(float);
		size = p_size * 4;
		break;
	case _Shader::SPT_MAT4:
		p_size = sizeof(float);
		size = p_size * 16;
		break;
	case _Shader::SPT_TEXTURE:
		break;
	default:
		break;
	}
	_ASSERT_EXPR(value&&size > 0, "setUniform Error!");
	if (!m_value)
		m_value = (uint8_t*)malloc(size);
	memset(m_value, 0, size);
	memcpy(m_value, value, std::min(size, p_size * count));
}

void _Shader::ShaderProgram::Uniform::update(ShaderProgram * program)
{
	switch (m_type)
	{
	case _Shader::SPT_UNKNOWN:
		break;
	case _Shader::SPT_INT:
		glUniform1i(m_location, *((GLint*)m_value));
		break;
	case _Shader::SPT_FLOAT:
		glUniform1f(m_location, *((GLfloat*)m_value));
		break;
	case _Shader::SPT_VEC2:
		glUniform2f(m_location, *((GLfloat*)m_value), *((GLfloat*)m_value+1));
		break;
	case _Shader::SPT_VEC3:
		glUniform3f(m_location, *((GLfloat*)m_value), *((GLfloat*)m_value + 1), *((GLfloat*)m_value + 2));
		break;
	case _Shader::SPT_VEC4:
		glUniform4f(m_location, *((GLfloat*)m_value), *((GLfloat*)m_value + 1), *((GLfloat*)m_value + 2), *((GLfloat*)m_value + 3));
		break;
	case _Shader::SPT_MAT4:
		glUniformMatrix4fv(m_location, 1, false, (GLfloat*)m_value);
		break;
	case _Shader::SPT_TEXTURE:
		break;
	default:
		break;
	}
}
