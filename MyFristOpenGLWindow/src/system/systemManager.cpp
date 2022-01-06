#include "systemManager.h"
#include "inputSystem.h"
#include "sceneSystem.h"
#include "entityCreateSystem.h"
#include "entityRelationSystem.h"
#include "entityComponentSystem.h"
#include "entityTransformSystem.h"
#include "entityRenderSystem.h"
#include "entityDestorySystem.h"
#include <algorithm>
SystemManager::SystemManager()
{
	add(new InputSystem());
	add(new SceneSystem());
	add(new EntityCreateSystem());
	add(new EntityRelationSystem());
	add(new EntityComponentSystem());
	add(new EntityTransformSystem());
	add(new EntityRenderSystem());
	add(new EntityDestorySystem());
}

SystemManager::~SystemManager()
{
	for (size_t i = m_system.size(); i > 0; i--)
	{
		auto sys = m_system[i - 1];
		m_system.pop_back();
		delete sys;
	}
}

void SystemManager::add(System* sys)
{
	if (sys->getSystemType() == 0)
		return;
	for (auto iter : m_system)
	{
		if (iter->getSystemType() == sys->getSystemType())
			return;
	}
	m_system.push_back(sys);
	std::sort(m_system.begin(), m_system.end(), m_cmp);
}

void SystemManager::pushSystemCommand(SystemCommand _commond)
{
	m_commonds.push_back(_commond);
}

void SystemManager::tick()
{
	for (auto _commond : m_commonds)
	{
		System* sys = getSystem(_commond.m_type);
		if (sys)
		{
			sys->pushCommand(_commond);
		}
	}
	for (auto sys : m_system)
	{
		sys->execute();
	}
	m_commonds.clear();
}

System* SystemManager::getSystem(uint16_t type)
{
	for (auto sys : m_system)
	{
		if (sys->getSystemType() == type)
		{
			return sys;
		}
	}
	return nullptr;
}
