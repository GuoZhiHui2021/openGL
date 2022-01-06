#include "world.h"
#include <common/time.h>
#include "sceneManager.h"
#include <system/systemManager.h>
#include <render/renderManager.h>
World::World()
{
	last_frame_millitm = getCurMillitm() - m_timeInterval;
}

World::~World()
{
}

void World::setFrameRate(uint16_t frameRate)
{
	m_frameRate = frameRate;
	m_timeInterval = 1.0 / m_frameRate * 1000;
}

void World::tick()
{
	if (m_frameRate <= 0)
		return;
	time_t curTime = getCurMillitm();
	if (curTime - last_frame_millitm < m_timeInterval)
	{
		return;
	}
	m_tickInterval = curTime - last_frame_millitm;
	last_frame_millitm = curTime;
	if (curTime - last_second_millitm >= m_timeInterval * m_frameRate)
	{
		m_last_frameRate = m_cur_frameRate;
		m_cur_frameRate = 0;
	}
	m_cur_frameRate++;
	m_worldTime_millitm += m_timeInterval;
	SystemManager::Instance()->tick();
	SceneManager::Instance()->update();
	RenderManager::Instance()->update();
}
