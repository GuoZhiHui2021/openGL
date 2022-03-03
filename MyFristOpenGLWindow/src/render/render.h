#pragma once
#include "render/shaderProgram.h"
#include <unordered_map>
#include "render/shader.h"
using namespace _Shader;

struct TextureData
{
	char name[127] = {};
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
	int64_t id = 0;
	TextureData* textures;
	UniformData* uniforms;
	float transform[16] = {0};
	bool useUV[8] = { false,false,false,false,false,false,false,false };
	bool useColor = false;
	int textureSize = 0;
	int uniformSize = 0;
	int elementCount = 0;
	int stencilRef = 0;
	unsigned int cullFace = 0;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;
	RenderData():textures(nullptr), uniforms(nullptr)
	{}
	~RenderData()
	{
		if (textures)
		{
			free(textures);
			textures = nullptr;
		}
		if (uniforms)
		{
			for (int i = 0; i < uniformSize; i++)
			{
				free(uniforms[i].m_data);
				uniforms[i].m_data = nullptr;
			}
			free(uniforms);
			uniforms = nullptr;
		}
	}
};

struct BaseLightData
{
	float ambient[3] = { 0 };
	float diffuse[3] = { 0 };
	float specular[3] = { 0 };
};

struct DirectionalLightData :public BaseLightData
{
	float direction[3] = { 0 };
	float strength = 1;
};

struct PointLightData :public BaseLightData
{
	float position[3] = { 0 };
	float constant = 0;
	float linear = 0;
	float quadratic = 0;
	float strength = 1;
};

struct SpotLightData :public BaseLightData
{
	float position[3] = { 0 };
	float direction[3] = { 0 };
	float cutOff = 0;
	float outCutOff = 0;
	float strength = 1;
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
	RenderData* getRenderData(int64_t id);
	void removeRenderData(int64_t id);
	void removeDatas();
protected:
	ShaderProgram* m_program;
	bool m_initialized;
	GLenum m_face;
	GLenum m_mode;
	std::unordered_map<int64_t, RenderData*> m_renderDatas;
};

class OutlineRender:public Render
{
public:
	virtual void render() override;
private:

};

