#include "system.h"
#include <scene/sceneManager.h>
Entity* System::getEntity(int64_t id)
{
	Scene* scene = SceneManager::Instance()->queryEntityScene(id);
	if (scene)
	{
		return scene->getEntity(id);
	}
	return nullptr;
}
