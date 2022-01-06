#include "entityRenderSystem.h"
#include <scene/sceneManager.h>
#include <render/materialManager.h>
#include <render/renderManager.h>
#include <scene/world.h>
#include <scene/transformComponent.h>
#include <scene/renderComponent.h>
#include <common/fileUtil.h>
#include <common/util.h>
#include <queue>
bool getEntityRenderValue(std::string str, int64_t& id, std::string& value)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	if (!strToInt64(strs[0].c_str(), t_id))
		return false;
	id = t_id;
	value = strs[1];
	return true;
}
void EntityRenderSystem::execute_implement()
{
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_Visible:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Material:exe<2>(m_commands[i].m_data); break;
		default:
			break;
		}
	}
	auto scene = SceneManager::Instance()->getCurScene();
	if (scene)
	{
		auto interval = World::Instance()->getTickInterval();
		for (Entity* entity : scene->getEntities())
		{
			updateRenderData(entity);
		}
	}
}

void EntityRenderSystem::updateRenderData(Entity* entity)
{
	auto r_component = entity->getComponent<RenderComponent>();
	auto t_component = entity->getComponent<TransformComponent>();
	if (r_component && r_component->getVisible())
	{
		Transfrom t;
		if (t_component)
			t = t_component->getTransfrom();
		std::string material = r_component->getMaterial();
		RenderData* data = new RenderData();
		std::queue<UniformData> uniforms;
		std::queue<TextureData> textures;
		unsigned int verticesCount;
		unsigned int elementsCount;
		void* vertices = entity->getRenderVerticesBuffer(verticesCount);
		void* elements = entity->getRenderElementsBuffer(elementsCount);
		if (!vertices||!elements)
		{
			if (vertices)
				free(vertices);
			if (elements)
				free(elements);
			delete data;
			return;
		}
		data->vertices = (float*)vertices;
		data->count = verticesCount;
		data->element = (unsigned int*)elements;
		data->element_count = elementsCount;
		if (Material* materialInstance = MaterialManager::Instance()->getOrCreateMaterial(material))
		{
			std::vector<MaterialPrototypeAttr> attrs = materialInstance->getAttrs();
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
					uniforms.emplace();
					uniforms.back().m_data = attr.m_value;
					uniforms.back().m_type = attr.m_type;
					memcpy_s(uniforms.back().m_name, strlen(attr.m_name.c_str())+1, attr.m_name.c_str(), strlen(attr.m_name.c_str())+1);
					break;
				case GL_TEXTURE0:
				case GL_TEXTURE1:
				case GL_TEXTURE2:
				case GL_TEXTURE3:
				case GL_TEXTURE4:
				case GL_TEXTURE5:
				case GL_TEXTURE6:
				case GL_TEXTURE7:
					textures.emplace();
					for (size_t i = 0; i < 4; i++)
					{
						textures.back().options[i] = *((uint16_t*)attr.m_value + i);
					}
					textureName = (char*)((uint16_t*)attr.m_value + 4);
					textures.back().textureUnit = attr.m_type;
					memcpy_s(textures.back().texture, strlen(textureName)+1, textureName, strlen(textureName)+1);
					free(attr.m_value);
					textureName = nullptr;
					break;
				default:
					break;
				}
			}
			data->id = entity->getInstanceId();
			data->prototype = materialInstance->getPrototype();
			data->uniformSize = uniforms.size();
			data->uniforms = (UniformData*)malloc(sizeof(UniformData) * data->uniformSize);
			data->textureSize = textures.size();
			data->textures = (TextureData*)malloc(sizeof(TextureData) * data->textureSize);
			data->useUV[0] = true;
			if (data->uniforms)
			{
				size_t i = 0;
				while (!uniforms.empty())
				{
					memcpy_s(data->uniforms + i, sizeof(UniformData), &uniforms.front(), sizeof(UniformData));
					data->uniforms[i++].m_data = uniforms.front().m_data;
					uniforms.front().m_data = nullptr;
					uniforms.pop();
				}
			}
			if (data->textures)
			{
				size_t i = 0;
				while (!textures.empty())
				{
					memcpy_s(data->textures + i++, sizeof(TextureData), &textures.front(), sizeof(TextureData));
					textures.pop();
				}
			}
			memcpy_s(data->transform, sizeof(float) * 16, t.value(), sizeof(float) * 16);
			RenderManager::Instance()->updateRenderData(data);
		}
		else
		{
			free(vertices);
			free(elements);
			delete data;
			return;
		}
	}
}

template<>
void EntityRenderSystem::exe<1>(std::string exeCommand)
{
	bool visible;
	int64_t id;
	std::string s_visible;
	if (getEntityRenderValue(exeCommand, id, s_visible)&&strToBool(s_visible.c_str(), visible))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<RenderComponent>();
			if (component)
				component->setVisible(visible);
		}
	}
}

template<>
void EntityRenderSystem::exe<2>(std::string exeCommand)
{
	int64_t id;
	std::string material;
	if (getEntityRenderValue(exeCommand, id, material))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<RenderComponent>();
			removeHTSpaces(material);
			if (component)
				component->setMaterial(material);
		}
	}
}
