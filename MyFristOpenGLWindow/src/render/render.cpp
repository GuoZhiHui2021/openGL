#include "render.h"
#include "vertexShader.h"
#include "fragmentShader.h"
#include "shaderManager.h"
#include "textureManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace _Shader;
Render::Render() :m_program(nullptr), m_initialized(false), m_face(GL_FRONT_AND_BACK), m_mode(GL_FILL)
{
	
}

Render::~Render()
{
	if (m_program)
	{
		delete m_program;
		m_program = nullptr;
	}
}

bool Render::attachShader(unsigned int shaderType, const GLchar * shaderName)
{
	Shader* shader = ShaderManager::Instance()->getShader(shaderType, shaderName);
	_ASSERT_EXPR(shader != nullptr, "AttachShader Error!");
	m_program->attach(shader);
	return true;
}

void Render::initialize()
{
	if (m_program)
	{
		delete m_program;
		m_program = nullptr;
	}
	m_program = new ShaderProgram();
	m_initialized = false;
}

void Render::initialized()
{
	if (m_program)
	{
		m_program->link();
		m_initialized = true;
	}	
}

void Render::setPolygonMode(GLenum face, GLenum mode)
{
	m_face = face;
	m_mode = mode;
}

void Render::render()
{
	if (!m_initialized || !m_program)
		return;
	if (m_program)
		m_program->use();

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 view(1.0f);
	// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	setUniform("viewMat", ShaderProgram::convertToShaderParamType(GL_FLOAT_MAT4), glm::value_ptr(view));
	setUniform("projectionMat", ShaderProgram::convertToShaderParamType(GL_FLOAT_MAT4), glm::value_ptr(projection));


	for (auto iter = m_renderDatas.begin(); iter != m_renderDatas.end(); iter++)
	{
		auto data = iter->second;
		if (!data->active)
			continue;
		for (int i = 0; i < data->uniformSize; i++)
		{
			setUniform(std::string(data->uniforms[i].m_name, strlen(data->uniforms[i].m_name)), ShaderProgram::convertToShaderParamType(data->uniforms[i].m_type), data->uniforms[i].m_data);	
		}
		
		setUniform("modelMat", ShaderProgram::convertToShaderParamType(GL_FLOAT_MAT4), data->transform);
		
		m_program->update();
		for (int i = 0; i < data->textureSize; i++)
		{
			TextureData textureData = data->textures[i];
			std::string textureName(textureData.texture, strlen(textureData.texture));
			uint16_t* options = textureData.options;
			Texture* texture = TextureManager::Instance()->getOrCreateTexture(textureName);
			if (texture)
			{
				switch (textureData.textureUnit)
				{
				case GL_TEXTURE0:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.texture), 0); break;
				case GL_TEXTURE1:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.texture), 1); break;
				case GL_TEXTURE2:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.texture), 2); break;
				case GL_TEXTURE3:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.texture), 3); break;
				case GL_TEXTURE4:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.texture), 4); break;
				case GL_TEXTURE5:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.texture), 5); break;
				case GL_TEXTURE6:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.texture), 6); break;
				case GL_TEXTURE7:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.texture), 7); break;
				default:
					break;
				}
				texture->use(textureData.textureUnit, options);
			}
		}
		glBindVertexArray(data->VAO);
		glPolygonMode(m_face, m_mode);
		glDrawElements(GL_TRIANGLES, data->element_count, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void Render::loadData(RenderData * data)
{
	if (!m_program || data->id <= 0||!data->count||!data->element_count)
		return;
	if (m_renderDatas.find(data->id) != m_renderDatas.end())
	{
		auto old_data = m_renderDatas[data->id];
		m_renderDatas.erase(data->id);
		delete old_data;
	}
	m_renderDatas.insert(std::make_pair(data->id, data));
	if (!data->VAO)
	{
		glGenVertexArrays(1, &data->VAO);
		glBindVertexArray(data->VAO);
	}
	if (!data->VBO)
	{
		glGenBuffers(1, &data->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, data->VBO);
	}
	if (!data->EBO)
	{
		glGenBuffers(1, &data->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->EBO);
	}
	size_t p_size = 3;
	if (data->useColor)
		p_size += 3;
	if (data->useAlpha)
		p_size += 1;
	for (size_t i = 0; i < sizeof(data->useUV); i++)
	{
		if (data->useUV[i])
			p_size += 2;
	}
	
	size_t c_size = 0;
	glBufferData(GL_ARRAY_BUFFER, data->count * p_size * sizeof(float), data->vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->element_count * sizeof(unsigned int), data->element, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
	glEnableVertexAttribArray(0);
	c_size += 3;
	if (data->useColor)
	{
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
		glEnableVertexAttribArray(1);
		c_size += 3;
	}
	if (data->useAlpha)
	{
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
		glEnableVertexAttribArray(2);
		c_size += 1;
	}
	for (size_t i = 0;i < sizeof(data->useUV); i++)
	{
		if (data->useUV[i])
		{
			glVertexAttribPointer(3 + i, 2, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
			glEnableVertexAttribArray(3+i);
			c_size += 2;
		}
	}
	glBindVertexArray(0);
}

void Render::updateData(int64_t id)
{
	if (m_renderDatas.find(id) == m_renderDatas.end())
		return;
	auto iter = m_renderDatas.find(id);
	RenderData* data = iter->second;

	size_t p_size = 3;
	if (data->useColor)
		p_size += 3;
	if (data->useAlpha)
		p_size += 1;
	for (size_t i = 0; i < sizeof(data->useUV); i++)
	{
		if (data->useUV[i])
			p_size += 2;
	}


	size_t c_size = 0;
	glBindVertexArray(data->VAO);
	glBufferData(GL_ARRAY_BUFFER, data->count * p_size * sizeof(float), data->vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->element_count * sizeof(unsigned int), data->element, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
	glEnableVertexAttribArray(0);
	c_size += 3;
	if (data->useColor)
	{
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
		glEnableVertexAttribArray(1);
		c_size += 3;
	}
	if (data->useAlpha)
	{
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
		glEnableVertexAttribArray(2);
		c_size += 1;
	}
	for (size_t i = 0; i < sizeof(data->useUV); i++)
	{
		if (data->useUV[i])
		{
			glVertexAttribPointer(3 + i, 2, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
			glEnableVertexAttribArray(3 + i);
			c_size += 2;
		}
	}
	glBindVertexArray(0);
}

RenderData* Render::getRenderData(int64_t id)
{
	auto iter = m_renderDatas.find(id);
	if (iter != m_renderDatas.end())
	{
		return iter->second;
	}
	return nullptr;
}

void Render::deleteRenderData(int64_t id)
{
	auto iter = m_renderDatas.find(id);
	if (iter != m_renderDatas.end())
	{
		auto data = iter->second;
		m_renderDatas.erase(id);
		delete data;
	}
}

void Render::removeRenderData(int64_t id)
{
	auto iter = m_renderDatas.find(id);
	if (iter != m_renderDatas.end())
	{
		auto data = iter->second;
		m_renderDatas.erase(id);
	}
}

void Render::removeDatas()
{
	for (auto iter : m_renderDatas)
	{
		removeRenderData(iter.first);
	}
}




