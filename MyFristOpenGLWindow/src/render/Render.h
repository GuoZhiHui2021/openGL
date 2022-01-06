#pragma once
#include "render/shaderProgram.h"
#include <unordered_map>
#include "render/shader.h"
using namespace _Shader;

struct TextureData
{
	char texture[127] = {};
	uint16_t textureUnit = 0;
	uint16_t options[8] = { GL_REPEAT,GL_REPEAT,GL_NEAREST,GL_NEAREST,0x0000,0x0000,0x0000,0x0000};
};
struct UniformData
{
	char m_name[127] = {};
	uint16_t m_type;
	void* m_data;
	UniformData():m_type(0), m_data(nullptr)
	{}
	~UniformData()
	{
		if (m_data)
		{
			free(m_data);
			m_data = nullptr;
		}
	}
};
//float* vertices/  float* uv/float* color/ float* alpha/
struct RenderData
{
	std::string prototype;
	bool active = true;
	int64_t id = 0;
	unsigned int count = 0;
	unsigned int element_count = 0;
	unsigned int texture_name_length = 0;
	float* vertices;
	unsigned int* element;
	TextureData* textures;
	UniformData* uniforms;
	float transform[16] = {0};
	bool useUV[2] = { false,false };
	bool useColor = false;
	bool useAlpha = false;
	int textureSize = 0;
	int uniformSize = 0;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;
	RenderData():vertices(nullptr),element(nullptr), textures(nullptr), uniforms(nullptr)
	{}
	~RenderData()
	{
		if (VAO) 
			glDeleteVertexArrays(1, &VAO);
		if (VBO)
			glDeleteBuffers(1, &VBO);
		if (EBO)
			glDeleteBuffers(1, &VBO);
		if (vertices)
		{
			free(vertices);
			vertices = nullptr;
		}
		if (element)
		{
			free(element);
			element = nullptr;
		}
		if (textures)
		{
			free(textures);
			textures = nullptr;
		}
		if (uniforms)
		{
			free(uniforms);
			uniforms = nullptr;
		}
	}
};

class Render
{
protected:
	
public:
	Render();
	~Render();
	bool attachShader(unsigned int,const GLchar*);
	void setUniform(const std::string &name, ShaderParamType pType,void* value, uint8_t count = 0 )
	{
		
		_ASSERT_EXPR(m_program, "setUniform Error!program is nullptr");
		m_program->setUniform(name, pType, value, count);
	}
	virtual void initialize();
	void initialized();
	void setPolygonMode(GLenum face, GLenum mode);
	virtual void render();
	virtual void loadData(RenderData* data);
	virtual void updateData(int64_t id);
	RenderData* getRenderData(int64_t id);
	void deleteRenderData(int64_t id);
	void removeRenderData(int64_t id);
	void removeDatas();
protected:
	ShaderProgram* m_program;
	bool m_initialized;
	GLenum m_face;
	GLenum m_mode;
	std::unordered_map<int64_t, RenderData*> m_renderDatas;
};

