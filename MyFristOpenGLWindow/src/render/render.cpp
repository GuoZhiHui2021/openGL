#include "render.h"
#include "vertexShader.h"
#include "fragmentShader.h"
#include "shaderManager.h"
#include "textureManager.h"
#include "renderManager.h"
#include <scene/cameraManager.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <render/def.h>
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

	Transfrom projectionTransfrom = CameraManager::Instance()->getPerspectiveTransfrom();
	Transfrom viewTransfrom = CameraManager::Instance()->getViewTransfrom();
	Vector3 cameraDirection = CameraManager::Instance()->getMainCameraDirection();

	setUniform("viewMat", ShaderProgram::convertToShaderParamType(GL_FLOAT_MAT4), viewTransfrom.value());
	setUniform("projectionMat", ShaderProgram::convertToShaderParamType(GL_FLOAT_MAT4), projectionTransfrom.value());
	setUniform("viewDir", ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), cameraDirection.value());
	auto directionalLightDatas = RenderManager::Instance()->getDirectionalLightDatas();
	auto pointLightDatas = RenderManager::Instance()->getPointLightData();
	auto spotLightDatas = RenderManager::Instance()->getSpotLightData();

	//directionalLight
	int dirCount = directionalLightDatas.size();
	setUniform("directionalLightDataCount", ShaderProgram::convertToShaderParamType(GL_INT), &dirCount);
	for (int i = 0; i < dirCount; i++)
	{
		char s[127];
		sprintf_s(s, "directionalLights[%d]", i);
		size_t len = strlen(s);

		strcpy_s(s + len, strlen(".ambient")+1, ".ambient");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), directionalLightDatas[i].ambient);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".diffuse")+1, ".diffuse");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), directionalLightDatas[i].diffuse);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".specular")+1, ".specular");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), directionalLightDatas[i].specular);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".direction")+1, ".direction");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), directionalLightDatas[i].direction);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".strength") + 1, ".strength");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT), &(directionalLightDatas[i].strength));
	}

	//pointLight
	int pointCount = pointLightDatas.size();
	setUniform("pointLightDataCount", ShaderProgram::convertToShaderParamType(GL_INT), &pointCount);
	for (int i = 0; i < pointCount; i++)
	{
		char s[127];
		sprintf_s(s, "pointLights[%d]", i);
		size_t len = strlen(s);

		strcpy_s(s + len, strlen(".ambient") + 1, ".ambient");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), pointLightDatas[i].ambient);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".diffuse")+1, ".diffuse");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), pointLightDatas[i].diffuse);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".specular")+1, ".specular");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), pointLightDatas[i].specular);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".position")+1, ".position");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), pointLightDatas[i].position);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".constant")+1, ".constant");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT), &(pointLightDatas[i].constant));
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".linear")+1, ".linear");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT), &(pointLightDatas[i].linear));
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".quadratic")+1, ".quadratic");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT), &(pointLightDatas[i].quadratic));
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".strength") + 1, ".strength");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT), &(pointLightDatas[i].strength));
	}

	//spotLight
	int spotCount = spotLightDatas.size();
	setUniform("spotLightDataCount", ShaderProgram::convertToShaderParamType(GL_INT), &spotCount);
	for (int i = 0; i < spotCount; i++)
	{
		char s[127];
		sprintf_s(s, "spotLights[%d]", i);
		size_t len = strlen(s);

		strcpy_s(s + len, strlen(".ambient")+1, ".ambient");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), spotLightDatas[i].ambient);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".diffuse")+1, ".diffuse");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), spotLightDatas[i].diffuse);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".specular")+1, ".specular");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), spotLightDatas[i].specular);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".position")+1, ".position");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), spotLightDatas[i].position);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".direction")+1, ".direction");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT_VEC3), spotLightDatas[i].direction);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".cutOff")+1, ".cutOff");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT), &(spotLightDatas[i].cutOff));
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".outCutOff") + 1, ".outCutOff");
		float outCutOff = std::min(spotLightDatas[i].outCutOff, spotLightDatas[i].cutOff);
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT), &outCutOff);
		memset(s + len, 0, 127 - len);
		strcpy_s(s + len, strlen(".strength") + 1, ".strength");
		setUniform(s, ShaderProgram::convertToShaderParamType(GL_FLOAT), &(spotLightDatas[i].strength));
	}

	for (auto iter = m_renderDatas.begin(); iter != m_renderDatas.end(); iter++)
	{
		auto data = iter->second;
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
				case GL_TEXTURE0:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.name), 0); break;
				case GL_TEXTURE1:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.name), 1); break;
				case GL_TEXTURE2:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.name), 2); break;
				case GL_TEXTURE3:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.name), 3); break;
				case GL_TEXTURE4:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.name), 4); break;
				case GL_TEXTURE5:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.name), 5); break;
				case GL_TEXTURE6:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.name), 6); break;
				case GL_TEXTURE7:glUniform1i(glGetUniformLocation(m_program->getProgramID(), textureData.name), 7); break;
				default:
					break;
				}
				texture->use(textureData.textureUnit, options);
			}
		}
		glBindVertexArray(data->VAO);
		glPolygonMode(m_face, m_mode);
		glStencilFunc(GL_ALWAYS, data->stencilRef, 0XFF);
		glStencilMask(0XFF);
			

		glDrawElements(GL_TRIANGLES, data->elementCount, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void Render::loadData(RenderData * data)
{
	if (!m_program || data->id <= 0)
	{
		delete data;
		return;
	}
	if (m_renderDatas.find(data->id) != m_renderDatas.end())
	{
		auto old_data = m_renderDatas[data->id];
		m_renderDatas.erase(data->id);
		delete old_data;
	}
	m_renderDatas.insert(std::make_pair(data->id, data));
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
	m_renderDatas.clear();
}

void OutlineRender::render()
{
	if (!m_initialized || !m_program)
		return;
	if (m_program)
		m_program->use();

	Transfrom projectionTransfrom = CameraManager::Instance()->getPerspectiveTransfrom();
	Transfrom viewTransfrom = CameraManager::Instance()->getViewTransfrom();

	setUniform("viewMat", ShaderProgram::convertToShaderParamType(GL_FLOAT_MAT4), viewTransfrom.value());
	setUniform("projectionMat", ShaderProgram::convertToShaderParamType(GL_FLOAT_MAT4), projectionTransfrom.value());

	glStencilMask(0X00);
	glDisable(GL_DEPTH_TEST);
	for (auto iter = m_renderDatas.begin(); iter != m_renderDatas.end(); iter++)
	{
		auto data = iter->second;
		for (int i = 0; i < data->uniformSize; i++)
		{
			setUniform(std::string(data->uniforms[i].m_name, strlen(data->uniforms[i].m_name)), ShaderProgram::convertToShaderParamType(data->uniforms[i].m_type), data->uniforms[i].m_data);
		}
		setUniform("modelMat", ShaderProgram::convertToShaderParamType(GL_FLOAT_MAT4), data->transform);

		m_program->update();
		glBindVertexArray(data->VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (data->stencilRef)
		{
			glStencilFunc(GL_NOTEQUAL, 1, 0XFF);
		}
		
		glDrawElements(GL_TRIANGLES, data->elementCount, GL_UNSIGNED_INT, 0);

	}
	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(0);
}
