#include "sceneManager.h"

SceneManager::SceneManager():m_curScene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(Scene* scene)
{
	for (Scene* _scene : m_scenes)
	{
		if (_scene == scene)
			return;
	}
	if (!m_curScene)
	{
		m_curScene = scene;
	}
		
	m_scenes.push_back(scene);
}

void SceneManager::switchScene(Scene* scene)
{
	if (m_curScene == scene)
		return;
	if (m_curScene)
	{
		std::vector<Entity*> entities = scene->separateSustainedEntities();
		for (auto entity : entities)
		{
			scene->addEntityDFS(entity);
		}
	}
	addScene(scene);
}

void SceneManager::removeScene(uint64_t sceneId)
{
	if (m_curScene && m_curScene->getInstanceId() == sceneId)
		return;
	auto iter = m_scenes.begin();
	for (; iter!= m_scenes.end(); iter++)
	{
		if ((*iter)->getInstanceId() == sceneId)
		{
			Scene* scene = (*iter);
			m_scenes.erase(iter);
			delete scene;
			break;
		}
	}
}

Scene* SceneManager::queryEntityScene(int64_t entityId)
{
	for (auto iter : m_scenes)
	{
		if (iter->getEntity(entityId))
			return iter;
	}
	return nullptr;
}

Scene* SceneManager::queryScene(int64_t entityId)
{
	for (auto iter : m_scenes)
	{
		if (iter->getSceneId()== entityId)
			return iter;
	}
}

void SceneManager::update()
{
	/*if (m_curScene)
		m_curScene->update();*/
}
