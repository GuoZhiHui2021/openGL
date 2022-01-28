#include "entityTransformSystem.h"
#include <scene/sceneManager.h>
#include <common/fileUtil.h>
#include <common/util.h>
#include <scene/transformComponent.h>
#include <scene/world.h>
bool getEntityTransformValue(std::string str,int64_t& id, std::vector<float>& value)
{
	value.clear();
	value.resize(3, 0);
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 4)
		return false;
	int64_t t_id = 0;
	std::vector<float> t_value(3, 0);
	if (!strToInt64(strs[0].c_str(), t_id))
		return false;
	for (size_t i = 1; i < 4; i++)
	{
		if (!strToFloat(strs[i].c_str(), t_value[i - 1]))
			return false;
	}
	id = t_id;
	value.swap(t_value);
	return true;
}

void EntityTransformSystem::execute_implement()
{
	
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_Velocity:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_AngularVelocity:exe<2>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Position:exe<3>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Rotation:exe<4>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Size:exe<5>(m_commands[i].m_data); break;
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
			if (m_positioned.find(entity->getInstanceId()) == m_positioned.end())
			{
				auto component = entity->getComponent<TransformComponent>();
				if (component&& component->getVelocity()!=Vector3())
				{
					if (m_changes.find(entity->getUniformId()) != m_changes.end())
						m_changes.insert(entity->getUniformId());
					component->setPosition(component->getPosition() + component->getVelocity() * interval / 1000.0f);
				}
			}
			if (m_rotationed.find(entity->getInstanceId()) == m_rotationed.end())
			{
				auto component = entity->getComponent<TransformComponent>();
				if (component && component->getAngularVelocity() != Vector3())
				{
					if (m_changes.find(entity->getUniformId()) != m_changes.end())
						m_changes.insert(entity->getUniformId());
					component->setRotation(component->getRotation() + component->getAngularVelocity() * interval / 1000.0f);
				}
			}
			
		}
		auto iter = m_changes.begin();
		while (iter != m_changes.end())
		{
			auto id = *iter;
			auto entity = scene->getEntity(id);
			iter++;
			while (!entity->isRoot() && entity->getParent() && m_changes.find(((Entity*)(entity->getParent()))->getUniformId()) == m_changes.end())
			{
				entity = (Entity*)(entity->getParent());
			}
			if(entity->getUniformId()!=id && m_changes.find(entity->getUniformId()) != m_changes.end())
					m_changes.erase(id);
		}
		
		auto func = [this](auto&& self, Entity* e) ->void {
			for (auto child : e->getChildren())
			{
				auto component = ((Entity*)child)->getComponent<TransformComponent>();
				if (component)
				{
					component->setParentWorldTransfrom(e->getComponent<TransformComponent>()->getWorldTransfrom());
					self(self, (Entity*)child);
				}
			}
		};

		iter = m_changes.begin();
		while (iter != m_changes.end())
		{
			auto id = *iter;
			auto entity = scene->getEntity(id);
			func(func, entity);
		}
	}
	m_positioned.clear();
	m_rotationed.clear();
	m_changes.clear();
}

template<>
void EntityTransformSystem::exe<1>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getEntityTransformValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<TransformComponent>();
			if (component)
				component->setVelocity(Vector3(value[0], value[1], value[2]));
		}
	}
}

template<>
void EntityTransformSystem::exe<2>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getEntityTransformValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<TransformComponent>();
			if (component)
				component->setAngularVelocity(Vector3(value[0], value[1], value[2]));
		}
	}
}

template<>
void EntityTransformSystem::exe<3>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getEntityTransformValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			if (m_positioned.find(id) == m_positioned.end())
				m_positioned.insert(id);
			auto component = entity->getComponent<TransformComponent>();
			if (component)
			{
				if (m_changes.find(id) != m_changes.end())
					m_changes.insert(id);
				component->setPosition(Vector3(value[0], value[1], value[2]));
			}
		}
	}
}

template<>
void EntityTransformSystem::exe<4>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getEntityTransformValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			if (m_rotationed.find(id) == m_rotationed.end())
				m_rotationed.insert(id);
			auto component = entity->getComponent<TransformComponent>();
			if (component)
			{
				if (m_changes.find(id) != m_changes.end())
					m_changes.insert(id);
				component->setRotation(Vector3(value[0], value[1], value[2]));
			}	
		}
	}
}

template<>
void EntityTransformSystem::exe<5>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getEntityTransformValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<TransformComponent>();
			if (component)
			{
				if (m_changes.find(id) != m_changes.end())
					m_changes.insert(id);
				component->setSize(Vector3(value[0], value[1], value[2]));
			}
		}
	}
}



