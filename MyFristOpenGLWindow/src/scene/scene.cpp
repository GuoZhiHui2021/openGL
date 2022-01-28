#include "scene.h"
#include "sceneManager.h"
#include "cameraManager.h"

bool Scene::add(Entity* entity)
{
	if (!entity)
		return false;
	if (m_entities.find(entity->getUniformId()) != m_entities.end())
		return false;
	if (SceneManager::Instance()->queryEntityScene(entity->getUniformId()) != nullptr)
		return false;
	m_entities[entity->getUniformId()] = entity;
	addChild(entity);

	return true;
}

bool Scene::addEntityDFS(Entity* entity)
{
	if (!entity)
		return false;
	if (m_entities.find(entity->getUniformId()) != m_entities.end())
		return false;
	if (SceneManager::Instance()->queryEntityScene(entity->getUniformId()) != nullptr)
		return false;
	auto func = [this](auto&& self,Entity* entity) ->void {
		for (auto child : entity->getChildren())
		{
			self(self, (Entity*)child);
			m_entities[((Entity*)child)->getUniformId()] = (Entity*)child;
			if (child->getInstanceType() == "Camera")
				CameraManager::Instance()->addCamera(((Entity*)child)->getUniformId());
		}
	};
	func(func, entity);
	m_entities[entity->getUniformId()] = entity;
	if (entity->getInstanceType() == "Camera")
		CameraManager::Instance()->addCamera(entity->getUniformId());
	addChild(entity);
	return true;
}

void Scene::remove(uint64_t entityId)
{
	if (m_entities.find(entityId) == m_entities.end())
	{
		return;
	}
	Entity* entity = m_entities[entityId];
	for (auto child : entity->getChildren())
	{
		remove(((Entity*)child)->getUniformId());
	}
	if (Instance* parent = entity->getParent())
	{
		parent->removeChild(entity->getInstanceId());
	}
	eraseEntity(entity);
	delete entity;
}

void Scene::remove(Entity* entity)
{
	remove(entity->getUniformId());
}

bool Scene::atScene(uint64_t entityId)
{
	if (m_entities.find(entityId) != m_entities.end())
		return true;
	return false;
}

Entity* Scene::getEntity(uint64_t entityId)
{
	if (m_entities.find(entityId) != m_entities.end())
		return m_entities[entityId];
	return nullptr;
}

void Scene::clear()
{
	auto iter = m_entities.begin();
	while (iter != m_entities.end())
	{
		Entity* entity = iter->second;
		iter++;
		eraseEntity(entity);
	}
	for (auto child : getChildren())
	{
		child->getParent()->removeChild(child->getInstanceId());
		delete child;
	}
}

std::vector<Entity*> Scene::separateSustainedEntities()
{
	std::vector<Entity*> entities;
	auto children = getChildren();
	for (auto child : children)
	{
		if (((Entity*)child)->isSustained())
		{
			removeFromEntities(((Entity*)child)->getUniformId());
			if (Instance* parent = child->getParent())
			{
				parent->removeChild(child->getInstanceId());
			}
			entities.push_back((Entity*)child);
		}
	}
	return entities;
}

std::vector<Entity*> Scene::getEntities()
{
	std::vector<Entity*> entities;
	auto iter = m_entities.begin();
	while (iter != m_entities.end())
	{
		entities.push_back(iter->second);
		iter++;
	}
	return entities;
}

void Scene::setParent_implement(Instance* instance)
{
	assert(0);
}

void Scene::removeFromEntities(uint64_t entityId)
{
	if (m_entities.find(entityId) == m_entities.end())
	{
		return;
	}
	Entity* entity = m_entities[entityId];
	for (auto child : entity->getChildren())
	{
		removeFromEntities(((Entity*)child)->getUniformId());
	}
	eraseEntity(entity);
}

void Scene::eraseEntity(Entity* entity)
{
	if (!entity)
		return;
	uint64_t uid = entity->getUniformId();
	if (m_entities.find(uid) != m_entities.end())
		m_entities.erase(uid);
	if (entity->getInstanceType() == "Camera")
	{
		CameraManager::Instance()->deleteCamera(uid);
	}
}
