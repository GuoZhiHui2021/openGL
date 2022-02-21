#include "mesh.h"
#include <render/render.h>
#include <render/materialManager.h>
#include <common/util.h>
void Mesh::getRenderDatas(std::vector<RenderData*>& datas, std::string materialType)
{
	//return datas;
    if(!m_isReady)
    {
		if (m_VAO)
			glDeleteVertexArrays(1, &m_VAO);
		if (m_VBO)
			glDeleteBuffers(1, &m_VBO);
		if (m_EBO)
			glDeleteBuffers(1, &m_EBO);
		m_VAO = 0;
		m_VBO = 0;
		m_EBO = 0;
        ready();

    }
    if (!m_isReady)
    {
        return;
    }
	datas.emplace_back(new RenderData());
	
    RenderData *data = datas.back();
    Material* material = MaterialManager::Instance()->getOrCreateMaterial(materialType);
	if(!material)
		material = MaterialManager::Instance()->getOrCreateMaterial(m_material);
    if (!material)
        material = MaterialManager::Instance()->getOrCreateMaterial("material/phong.materialPrototype");

    std::vector<UniformData> uniforms;
    std::vector<TextureData> textureDatas;
	std::vector<MaterialPrototypeAttr> attrs = material->getAttrs();
	for (auto attr : attrs)
	{
		char* textureName;
		switch (attr.m_type)
		{
		case GL_INT:
		case GL_FLOAT:
		case GL_FLOAT_VEC2:
		case GL_FLOAT_VEC3:
		case GL_FLOAT_VEC4:
			uniforms.emplace_back();
			uniforms.back().m_data = attr.m_value;
			uniforms.back().m_type = attr.m_type;
			memcpy_s(uniforms.back().m_name, strlen(attr.m_name.c_str()) + 1, attr.m_name.c_str(), strlen(attr.m_name.c_str()) + 1);
			break;
		case GL_TEXTURE0:
		case GL_TEXTURE1:
		case GL_TEXTURE2:
		case GL_TEXTURE3:
		case GL_TEXTURE4:
		case GL_TEXTURE5:
		case GL_TEXTURE6:
		case GL_TEXTURE7:
			textureDatas.emplace_back();
			for (size_t i = 0; i < 4; i++)
			{
				textureDatas.back().options[i] = *((uint16_t*)attr.m_value + i);
			}
			textureName = (char*)((uint16_t*)attr.m_value + 4);
			textureDatas.back().textureUnit = attr.m_type;
			memcpy_s(textureDatas.back().name, strlen(attr.m_name.c_str()) + 1, attr.m_name.c_str(), strlen(attr.m_name.c_str()) + 1);
			if (m_textures.find(textureDatas.back().name) != m_textures.end())
			{
				std::string nameStr(textureDatas.back().name);
				memcpy_s(textureDatas.back().texture, strlen(m_textures[nameStr].c_str()) + 1, m_textures[nameStr].c_str(), strlen(m_textures[nameStr].c_str()) + 1);
			}
			else
			{
				memcpy_s(textureDatas.back().texture, strlen(textureName) + 1, textureName, strlen(textureName) + 1);
			}
			free(attr.m_value);
			textureName = nullptr;
			break;
		default:
			break;
		}
	}
	data->uniformSize = uniforms.size();
	data->uniforms = (UniformData*)malloc(sizeof(UniformData) * data->uniformSize);
	data->textureSize = textureDatas.size();
	if (data->textureSize > 0)
		data->textures = (TextureData*)malloc(sizeof(TextureData) * data->textureSize);
	else
		data->textures = nullptr;
	for (int i = 0; i < m_numTexCoord; i++)
	{
		data->useUV[i] = true;
	}
	if (data->uniforms)
	{
		for (size_t i = 0; i < uniforms.size(); i++)
		{
			memcpy_s(data->uniforms + i, sizeof(UniformData), &(uniforms[i]), sizeof(UniformData));
			data->uniforms[i].m_data = (void*)uniforms[i].m_data;
			uniforms[i].m_data = nullptr;
		}
	}
	if (data->textures)
	{
		for (size_t i = 0; i < textureDatas.size(); i++)
		{
			memcpy_s(data->textures + i, sizeof(TextureData), &(textureDatas[i]), sizeof(TextureData));
		}
	}

    data->EBO = m_EBO;
	data->VAO = m_VAO;
	data->VBO = m_VBO;
	data->prototype = material->getPrototype();
	data->elementCount = m_indices.size();
	data->id = allocateId();
}

void Mesh::load(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::unordered_map<std::string, std::string>& textures, std::string material, int numTexCoord)
{
    if (vertices.empty() || indices.empty() || material.empty())
    {
        return;
    }
	m_vertices.clear();
	m_indices.clear();
	m_textures.clear();
	m_vertices.assign(vertices.begin(), vertices.end());
	m_indices.assign(indices.begin(), indices.end());
	m_textures = textures;
	m_material = material;
	m_numTexCoord = numTexCoord;
    m_isReady = false;
    m_isloaded = true;
}

void Mesh::setMaterial(std::string material)
{
	if (material == m_material)
		return;
	Material* materialInstance = MaterialManager::Instance()->getOrCreateMaterial(material);
	if (materialInstance)
	{
		m_material = material;
		m_isReady = false;
	}
}

Mesh::~Mesh()
{
	if (m_VAO)
		glDeleteVertexArrays(1, &m_VAO);
	if (m_VBO)
		glDeleteBuffers(1, &m_VBO);
	if (m_EBO)
		glDeleteBuffers(1, &m_EBO);
}

void Mesh::ready()
{
    if (!m_isloaded)
    {
        return;
    }

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	size_t p_size = 3;

	//normal
	p_size += 3;
	//texCoord
	p_size += 2 * m_numTexCoord;

	size_t c_size = 0;
	float* vertices = (float*)malloc(sizeof(float) * p_size * m_vertices.size());
	for (int i = 0; i < m_vertices.size(); i++)
	{
		memcpy_s(vertices + i * p_size, sizeof(float) * 3, m_vertices[i].position.value(), sizeof(float) * 3);
		memcpy_s(vertices + i * p_size + 3, sizeof(float) * 3, m_vertices[i].normal.value(), sizeof(float) * 3);
		for (int j = 0; j < m_numTexCoord; j++)
		{
			memcpy_s(vertices + i * p_size + 3 + 3 + j * 2, sizeof(float) * 2, m_vertices[i].texCoords[j].value(), sizeof(float) * 2);
		}
		
	}
	unsigned int* indices = (unsigned int*)malloc(sizeof(float) * m_indices.size());
	memcpy_s(indices, sizeof(float) * m_indices.size(), m_indices.data(), sizeof(float) * m_indices.size());
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * p_size * sizeof(float), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
	glEnableVertexAttribArray(0);
	c_size += 3;
	//color?

	//normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
	glEnableVertexAttribArray(2);
	c_size += 3;
	//texCoord
	for (size_t i = 0; i < m_numTexCoord; i++)
	{
		glVertexAttribPointer(3 + i, 2, GL_FLOAT, GL_FALSE, p_size * sizeof(float), (void*)(c_size * sizeof(float)));
		glEnableVertexAttribArray(3 + i);
		c_size += 2;
	}
	glBindVertexArray(0);
	free(vertices);
	free(indices);
    m_isReady = true;
}

void Model::getRenderDatas(std::vector<RenderData*>& datas, std::string material)
{
    for (auto iter : m_nodes)
    {
        iter->getRenderDatas(datas, material);
    }
}

void Model::add(MeshNodeInstance* node)
{
    m_nodes.push_back(node);
}
