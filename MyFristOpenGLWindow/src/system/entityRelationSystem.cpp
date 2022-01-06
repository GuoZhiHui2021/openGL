#include "entityRelationSystem.h"
#include <scene/sceneManager.h>
#include <common/fileUtil.h>
#include <common/util.h>
bool getEntityRelationValue(std::string str, int64_t& pid, int64_t& cid)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_pid = 0;
	int64_t t_cid = 0;
	std::vector<float> t_value(3, 0);
	if (!strToInt64(strs[0].c_str(), t_pid)|| !strToInt64(strs[1].c_str(), t_cid))
		return false;
	pid = t_pid;
	cid = t_cid;
	return pid>0&& cid>0&&pid!=cid;
}
void EntityRelationSystem::execute_implement()
{
	auto scene = SceneManager::Instance()->getCurScene();
	if (!scene)
		return;
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		int64_t pid, cid;
		if (getEntityRelationValue(m_commands[i].m_data, pid, cid))
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
