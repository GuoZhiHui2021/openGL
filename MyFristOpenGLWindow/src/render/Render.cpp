#include "Render.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderManager.h"
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

void Render::loadData(RenderData * data)
{
	if (!m_program || data->id <= 0||!data->count||!data->element_count)
		return;
	if (renderDatas.find(data->id) != renderDatas.end())
	{
		auto old_data = renderDatas[data->id];
		renderDatas.erase(data->id);
		delete old_data;
	}
	renderDatas.insert(std::make_pair(data->id, data));
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




