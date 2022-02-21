#include "entityComponentSystem.h"
#include <scene/sceneManager.h>
#include <common/fileUtil.h>
#include <common/util.h>
bool getEntityComponentValue(std::string str, int64_t& id, int64_t& type)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	int64_t t_type = 0;
	if (!strToInt64(strs[0].c_str(), t_id)||!strToInt64(strs[1].c_str(), t_type))
		return false;
	id = t_id;
	type = t_type;
	return true;
}
void EntityComponentSystem::execute_implement()
{
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_Add:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Remove:exe<2>(m_commands[i].m_data); break;
		default:
			break;
		}
	}
}

template<>
void EntityComponentSystem::exe<1>(std::string exeCommand)
{
	int64_t id,type;
	if (getEntityComponentValue(exeCommand,id, type))
	{
		if (Entity* entity = getEntity(id))
		{
			switch (type)
			{
			case static_cast<int64_t>(ComponentType::_TransformComponent):entity->applyComponent<TransformComponent>(); break;
			case static_cast<int64_t>(ComponentType::_RenderComponent):entity->applyComponent<RenderComponent>(); break;
			case static_cast<int64_t>(ComponentType::_DirectionalLightComponent):entity->applyComponent<DirectionalLightComponent>(); break;
			case static_cast<int64_t>(ComponentType::_PointLightComponent):entity->applyComponent<PointLightComponent>(); break;
			case static_cast<int64_t>(ComponentType::_SpotLightComponent):entity->applyComponent<SpotLightComponent>(); break;
			default:
				break;
			}
			
		}
	}
}

template<>
void EntityComponentSystem::exe<2>(std::string exeCommand)
{

	int64_t id, type;
	if (getEntityComponentValue(exeCommand, id, type))
	{
		if (Entity* entity = getEntity(id))
		{
			switch (type)
			{
			case static_cast<int64_t>(ComponentType::_TransformComponent):entity->removeComponent<TransformComponent>(); break;
			case static_cast<int64_t>(ComponentType::_RenderComponent):entity->removeComponent<RenderComponent>(); break;
			case static_cast<int64_t>(ComponentType::_DirectionalLightComponent):entity->removeComponent<DirectionalLightComponent>(); break;
			case static_cast<int64_t>(ComponentType::_PointLightComponent):entity->removeComponent<PointLightComponent>(); break;
			case static_cast<int64_t>(ComponentType::_SpotLightComponent):entity->removeComponent<SpotLightComponent>(); break;
			default:
				break;
			}

		}
	}
}
