#pragma once
#include <common/singleton.h>
#include <vector>
#include "scene.h"
class SceneManager:public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();
	Scene* getCurScene()
	{
		return m_curScene;
	}
	void addScene(Scene* scene);
	void switchScene(Scene* scene);
	void removeScene(uint64_t sceneId);
	Scene* queryEntityScene(int64_t entityId);
	Scene* queryScene(int64_t entityId);
	void update();
private:
	Scene* m_curScene;
	std::vector<Scene*> m_scenes;
	std::vector<uint64_t> m_removeScenes;
};

