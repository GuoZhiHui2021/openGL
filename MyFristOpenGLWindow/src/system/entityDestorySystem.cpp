#include "entityDestorySystem.h"
#include <scene/sceneManager.h>
#include <scene/cameraManager.h>
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
				destory(entity);
			}
		}
	}
}

void EntityDestorySystem::destory(Entity* entity)
{
	if (!entity)
		return;
	auto scene = SceneManager::Instance()->queryEntityScene(entity->getUniformId());
	scene->remove(entity->getUniformId());
}
