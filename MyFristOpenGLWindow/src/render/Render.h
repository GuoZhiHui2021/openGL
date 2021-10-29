#pragma once
#include "render/ShaderProgram.h"
#include <unordered_map>
#include "render/Shader.h"
using namespace _Shader;

struct TextureData
{
	char texture[127] = {};
	uint16_t textureUnit = 0;
	uint16_t options[8] = { GL_REPEAT,GL_REPEAT,GL_NEAREST,GL_NEAREST,0x0000,0x0000,0x0000,0x0000};
};
//float* vertices/  float* uv/float* color/ float* alpha/
struct RenderData
{
	unsigned int id = 0;
	unsigned int count = 0;
	unsigned int element_count = 0;
	unsigned int texture_name_length = 0;
	float* vertices;
	unsigned int* element;
	TextureData* textures;
	bool useUV[2] = { false,false };
	bool useColor = false;
	bool useAlpha = false;
	int textureSize = 0;
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;
	~RenderData()
	{
		if (VAO) 
			glDeleteVertexArrays(1, &VAO);
		if (VBO)
			glDeleteBuffers(1, &VBO);
		if (EBO)
			glDeleteBuffers(1, &VBO);
		//if (vertices)
		//	delete vertices;
		//if (element)
		//	delete element;
		//if (uv)
		//	delete uv;
		//if (color)
		//	delete color;
		//if (alpha)
		//	delete alpha;
		//if (texture)
		//	delete texture;
	}
};

class Render
{
protected:
	
public:
	Render();
	~Render();
	bool attachShader(unsigned int,const GLchar*);
	void setUniform(const std::string &name, void* value, uint8_t count, ShaderParamType pType)
	{
		
		_ASSERT_EXPR(m_program, "setUniform Error!program is nullptr");
		m_program->setUniform(name, value, count, pType);
	}
	virtual void initialize();
	void initialized();
	void setPolygonMode(GLenum face, GLenum mode);
	virtual void render() = 0;
	virtual void loadData(RenderData* data);
protected:
	ShaderProgram* m_program;
	bool m_initialized;
	GLenum m_face;
	GLenum m_mode;
	std::unordered_map<unsigned int, RenderData*> renderDatas;
};

