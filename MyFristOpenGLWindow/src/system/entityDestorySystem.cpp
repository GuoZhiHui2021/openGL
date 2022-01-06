#include "entityDestorySystem.h"
#include <scene/sceneManager.h>
#include <render/renderManager.h>
#include <common/util.h>
void EntityDestorySystem::execute_implement()
{
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		destory(m_commands[i].m_data);
	}
}

void EntityDestorySystem::destory(std::string data)
{
	int64_t id = 0;
	if (strToInt64(data.c_str(), id) && id > 0)
	{
		auto scene = SceneManager::Instance()->queryEntityScene(id);
		if (scene)
		{
			auto entity = scene->getEntity(id);
			if (entity)
			{
				destory(entity,true);
			}
		}
	}
}

void EntityDestorySystem::destory(Entity* entity,bool removeFromParent)
{
	auto scene = SceneManager::Instance()->queryEntityScene(entity->getUniformId());
	for (auto child: entity->getChildren())
	{
		destory((Entity*)child);
	}
	RenderManager::Instance()->destory(entity->getInstanceId());
	scene->remove(entity->getUniformId());
	Instance* parent = entity->getParent();
	if (removeFromParent && parent)
	{
		parent->removeChild(entity->getInstanceId());
		delete entity;
	}
}
