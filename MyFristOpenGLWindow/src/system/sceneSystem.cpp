#include "sceneSystem.h"
#include <scene/sceneManager.h>
#include <algorithm>
#include <common/util.h>
void SceneSystem::execute_implement()
{
	std::sort(m_commands.begin(), m_commands.end(), [](SystemCommand A, SystemCommand B) {return A.m_option < B.m_option; });
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_Create:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Switch:exe<2>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Remove:exe<3>(m_commands[i].m_data); break;
		default:
			break;
		}
	}
}

template<>
void SceneSystem::exe<1>(std::string exeCommand)
{
	int64_t id;
	if (strToInt64(exeCommand.c_str(), id)&&!SceneManager::Instance()->queryScene(id))
	{
		Scene* scene = new Scene();
		scene->setSceneId(id);
		SceneManager::Instance()->addScene(scene);
	}
}

template<>
void SceneSystem::exe<2>(std::string exeCommand)
{
	int64_t id;
	if (strToInt64(exeCommand.c_str(), id) && SceneManager::Instance()->queryScene(id))
	{
		Scene* curScene = SceneManager::Instance()->getCurScene();
		Scene* scene = SceneManager::Instance()->queryScene(id);
		if (curScene&& curScene!= scene)
		{
			SceneManager::Instance()->switchScene(scene);
		}
		
		                                                                             
	}
}

template<>
void SceneSystem::exe<3>(std::string exeCommand)
{
	int64_t id;
	if (strToInt64(exeCommand.c_str(), id))
	{
		SceneManager::Instance()->removeScene(id);
	}
}

