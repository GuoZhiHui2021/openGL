#include "entityCreateSystem.h"
#include <scene/box.h>
#include <scene/camera.h>
#include <scene/sceneManager.h>
#include <scene/cameraManager.h>
#include <common/util.h>
void EntityCreateSystem::execute_implement()
{
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_Box:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Camrea:exe<2>(m_commands[i].m_data); break;
		default:
			break;
		}
	}
	
}

template<>
void EntityCreateSystem::exe<1>(std::string exeCommand)
{
	Scene* scene = SceneManager::Instance()->getCurScene();
	if (scene)
	{
		int64_t id = 0;
		if (strToInt64(exeCommand.c_str(), id) && id > 0)
		{
			Box* box = new Box();
			box->setUniformId(id);
			scene->add(box);
		}
	}
}

template<>
void EntityCreateSystem::exe<2>(std::string exeCommand)
{
	Scene* scene = SceneManager::Instance()->getCurScene();
	if (scene)
	{
		int64_t id = 0;
		if (strToInt64(exeCommand.c_str(), id) && id > 0)
		{
			Camera* camera = new Camera();
			camera->setUniformId(id);
			scene->add(camera);
			CameraManager::Instance()->addCamera(id);
		}
	}
}
