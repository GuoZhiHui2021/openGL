#include "entityRelationSystem.h"
#include <scene/sceneManager.h>
#include <common/fileUtil.h>
#include <common/util.h>

void EntityRelationSystem::execute_implement()
{
	auto scene = SceneManager::Instance()->getCurScene();
	if (!scene)
		return;
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		int64_t pid, cid;
		if (getInt64Value(m_commands[i].m_data, pid, cid)&& pid != cid)
		{
			Entity* p = scene->getEntity(pid);
			Entity* c = scene->getEntity(cid);
			if (p && c)
			{
				p->addChild(c);
			}
		}
		
	}
}
