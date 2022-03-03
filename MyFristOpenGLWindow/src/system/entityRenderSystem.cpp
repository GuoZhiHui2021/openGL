#include "entityRenderSystem.h"
#include <scene/sceneManager.h>
#include <render/materialManager.h>
#include <render/meshManager.h>
#include <render/renderManager.h>
#include <scene/world.h>
#include <scene/transformComponent.h>
#include <scene/renderComponent.h>
#include <scene/directionalLightComponent.h>
#include <scene/pointLightComponent.h>
#include <scene/spotLightComponent.h>
#include <common/fileUtil.h>
#include <common/util.h>
#include <queue>
#include <render/def.h>

void EntityRenderSystem::execute_implement()
{
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_Visible:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Material:exe<2>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Mesh:exe<3>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Outline:exe<4>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_OutlineColor:exe<5>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_OutlineWitdh:exe<6>(m_commands[i].m_data); break;
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
			updateLightData(entity);
		}
	}
}

void EntityRenderSystem::updateRenderData(Entity* entity)
{
	auto r_component = entity->getComponent<RenderComponent>();
	auto t_component = entity->getComponent<TransformComponent>();
	auto d_component = entity->getComponent<DirectionalLightComponent>();
	auto p_component = entity->getComponent<PointLightComponent>();
	auto s_component = entity->getComponent<SpotLightComponent>();
	if (d_component || p_component || s_component)
		return;
	if (r_component && r_component->getVisible()&& MeshManager::Instance()->getOrCreateMesh(r_component->getMesh()))
	{
		MeshNodeInstance* meshs = MeshManager::Instance()->getOrCreateMesh(r_component->getMesh());
		std::vector<RenderData*> renderDatas;
		meshs->getRenderDatas(renderDatas, r_component->getMaterial());
		if (renderDatas.empty())
			return;
		Transfrom t;
		if (t_component)
			t = t_component->getTransfrom();
		int addNum = 0;
		if (r_component->getOutline())
		{
			addNum+=2;
		}
		
		for(int i = 0;i< renderDatas.size();i++)
		{
			RenderData *renderData = renderDatas[i];
			memcpy_s((renderData->transform), sizeof(float) * 16, t.value(), sizeof(float) * 16);
			

			if (addNum > 1 && renderData->uniforms != nullptr)
			{
				UniformData* data = renderData->uniforms;
				renderData->uniforms = nullptr;
				renderData->uniforms = (UniformData*)realloc(data, sizeof(UniformData) * (renderData->uniformSize + addNum));
				if (!renderData->uniforms)
				{
					renderData->uniforms = (UniformData*)malloc(sizeof(UniformData) * (renderData->uniformSize + addNum));
					memcpy_s(renderData->uniforms, sizeof(UniformData) * renderData->uniformSize, data, sizeof(UniformData) * renderData->uniformSize);
					free(data);
				}
			}
			else if(addNum > 1)
				renderData->uniforms = (UniformData*)malloc(sizeof(UniformData) * (renderData->uniformSize + addNum));
			if (!renderData->uniforms)
			{
				delete renderData;
				continue;
			}

			if (r_component->getOutline())
			{
				renderData->uniformSize++;
				renderData->uniforms[renderData->uniformSize - 1].m_type = GL_FLOAT_VEC3;
				strcpy_s(renderData->uniforms[renderData->uniformSize - 1].m_name, strlen("outlineColor") + 1, "outlineColor");
				renderData->uniforms[renderData->uniformSize - 1].m_data = malloc(sizeof(float) * 3);
				memcpy_s(renderData->uniforms[renderData->uniformSize - 1].m_data, sizeof(float) * 3, r_component->getOutlineColor().value(), sizeof(float) * 3);

				renderData->uniformSize++;
				renderData->uniforms[renderData->uniformSize - 1].m_type = GL_FLOAT;
				strcpy_s(renderData->uniforms[renderData->uniformSize - 1].m_name, strlen("outlineWidth") + 1, "outlineWidth");
				renderData->uniforms[renderData->uniformSize - 1].m_data = malloc(sizeof(float));
				float outlineWidth = r_component->getOutlineWidth();
				memcpy_s(renderData->uniforms[renderData->uniformSize - 1].m_data, sizeof(float), &outlineWidth, sizeof(float));

				renderData->stencilRef |= OUTLINE_STENCIL_MARK;
			}
			renderData->cullFace = r_component->getCullFace();

			RenderManager::Instance()->updateRenderData(renderData);
		}
	}
}

void EntityRenderSystem::updateLightData(Entity* entity)
{
	auto d_component = entity->getComponent<DirectionalLightComponent>();
	auto p_component = entity->getComponent<PointLightComponent>();
	auto s_component = entity->getComponent<SpotLightComponent>();
	if (d_component)
	{
		DirectionalLightData data;
		memcpy_s(data.ambient, sizeof(float) * 3, d_component->getAmbient().value(), sizeof(float) * 3);
		memcpy_s(data.diffuse, sizeof(float) * 3, d_component->getDiffuse().value(), sizeof(float) * 3);
		memcpy_s(data.specular, sizeof(float) * 3, d_component->getSpecular().value(), sizeof(float) * 3);
		memcpy_s(data.direction, sizeof(float) * 3, d_component->getDirection().value(), sizeof(float) * 3);
		data.strength = d_component->getStrength();
		RenderManager::Instance()->addDirectionalLightData(data);
	}
	if (p_component)
	{
		PointLightData data;
		memcpy_s(data.ambient, sizeof(float) * 3, p_component->getAmbient().value(), sizeof(float) * 3);
		memcpy_s(data.diffuse, sizeof(float) * 3, p_component->getDiffuse().value(), sizeof(float) * 3);
		memcpy_s(data.specular, sizeof(float) * 3, p_component->getSpecular().value(), sizeof(float) * 3);
		Transfrom t;
		auto t_component = entity->getComponent<TransformComponent>();
		if (t_component)
		{
			t = t_component->getWorldTransfrom();
		}
		data.position[0] = t[3].x;
		data.position[1] = t[3].y;
		data.position[2] = t[3].z;
		data.constant = p_component->getConstant();
		data.linear = p_component->getLinear();
		data.quadratic = p_component->getQuadratic();
		data.strength = p_component->getStrength();
		RenderManager::Instance()->addPointLightData(data);
	}
	if (s_component)
	{
		SpotLightData data;
		memcpy_s(data.ambient, sizeof(float) * 3, s_component->getAmbient().value(), sizeof(float) * 3);
		memcpy_s(data.diffuse, sizeof(float) * 3, s_component->getDiffuse().value(), sizeof(float) * 3);
		memcpy_s(data.specular, sizeof(float) * 3, s_component->getSpecular().value(), sizeof(float) * 3);
		data.cutOff = s_component->getCutOff();
		data.outCutOff = s_component->getOutCutOff();
		Transfrom t;
		auto t_component = entity->getComponent<TransformComponent>();
		if (t_component)
		{
			t = t_component->getWorldTransfrom();
		}
		data.position[0] = t[3].x;
		data.position[1] = t[3].y;
		data.position[2] = t[3].z;
		memcpy_s(data.direction, sizeof(float) * 3, Vector3(t[2].x, t[2].y, t[2].z).normalize().value(), sizeof(float) * 3);
		data.strength = s_component->getStrength();
		RenderManager::Instance()->addSpotLightData(data);
	}
	if (d_component || p_component || s_component)
	{
		Vector3 color = d_component ? d_component->getDiffuse() : p_component ? p_component->getDiffuse() : s_component->getDiffuse();
		updateLightRenderData(entity, color);
	}
}

void EntityRenderSystem::updateLightRenderData(Entity* entity, Vector3 color)
{
	auto r_component = entity->getComponent<RenderComponent>();
	auto t_component = entity->getComponent<TransformComponent>();

	if (r_component && r_component->getVisible())
	{
		std::string material = r_component->getMaterial();
		MeshNodeInstance* meshs = MeshManager::Instance()->getOrCreateMesh(r_component->getMesh());
		std::vector<RenderData*> renderDatas;
		meshs->getRenderDatas(renderDatas, "material/light.materialPrototype");
		if (renderDatas.empty())
			return;
		Transfrom t;
		if (t_component)
			t = t_component->getTransfrom();
		for (auto renderData : renderDatas)
		{
			memcpy_s(renderData->transform, sizeof(float) * 16, t.value(), sizeof(float) * 16);
			renderData->uniformSize += 1;
			if (renderData->uniformSize > 1 && renderData->uniforms != nullptr)
			{
				UniformData* data = renderData->uniforms;
				renderData->uniforms = nullptr;
				renderData->uniforms = (UniformData*)realloc(data, sizeof(UniformData) * renderData->uniformSize);
				if (!renderData->uniforms)
				{
					renderData->uniforms = (UniformData*)malloc(sizeof(UniformData) * renderData->uniformSize);
					memcpy_s(renderData->uniforms, sizeof(UniformData) * (renderData->uniformSize - 1), data, sizeof(UniformData) * (renderData->uniformSize - 1));
				}
				free(data);
			}
			else
				renderData->uniforms = (UniformData*)malloc(sizeof(UniformData) * renderData->uniformSize);
			if (!renderData->uniforms)
			{
				delete renderData;
				continue;
			}
			renderData->uniforms[renderData->uniformSize - 1].m_type = GL_FLOAT_VEC3;
			strcpy_s(renderData->uniforms[renderData->uniformSize - 1].m_name, strlen("lightColor") + 1, "lightColor");
			renderData->uniforms[renderData->uniformSize - 1].m_data = malloc(sizeof(float) * 3);
			memcpy_s(renderData->uniforms[renderData->uniformSize - 1].m_data, sizeof(float) * 3, color.value(), sizeof(float) * 3);

			RenderManager::Instance()->updateRenderData(renderData);
		}
	}
}

template<>
void EntityRenderSystem::exe<1>(std::string exeCommand)
{
	bool visible;
	int64_t id;
	std::string s_visible;
	if (getStringValue(exeCommand, id, s_visible)&&strToBool(s_visible.c_str(), visible))
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
	if (getStringValue(exeCommand, id, material))
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
template<>
void EntityRenderSystem::exe<3>(std::string exeCommand)
{
	int64_t id;
	std::string mesh;
	if (getStringValue(exeCommand, id, mesh))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<RenderComponent>();
			removeHTSpaces(mesh);
			if (component)
				component->setMesh(mesh);
		}
	}
}

template<>
void EntityRenderSystem::exe<4>(std::string exeCommand)
{
	int64_t id;
	bool outline;
	if (getBoolValue(exeCommand, id, outline))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<RenderComponent>();
			if (component)
				component->setOutline(outline);
		}
	}
}

template<>
void EntityRenderSystem::exe<5>(std::string exeCommand)
{
	int64_t id;
	std::vector<float> outlineColor;
	if (getV3Value(exeCommand, id, outlineColor))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<RenderComponent>();
			if (component)
				component->setOutlineColor(Vector3(outlineColor[0], outlineColor[1], outlineColor[2]));
		}
	}
}

template<>
void EntityRenderSystem::exe<6>(std::string exeCommand)
{
	int64_t id;
	float outlineWidth;
	if (getFloatValue(exeCommand, id, outlineWidth))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<RenderComponent>();
			if (component)
				component->setOutlineWidth(outlineWidth);
		}
	}
}

template<>
void EntityRenderSystem::exe<7>(std::string exeCommand)
{
	int64_t id;
	unsigned int cullFace;
	if (getUIntValue(exeCommand, id, cullFace))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<RenderComponent>();
			if (component)
				component->setCullFace(cullFace);
		}
	}
}
