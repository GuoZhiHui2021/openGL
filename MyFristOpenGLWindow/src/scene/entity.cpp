#include "entity.h"
#include "scene.h"
#include <render/materialManager.h>
#include <render/renderManager.h>
Entity::~Entity()
{
}

template<>
TransformComponent* Entity::getComponent<TransformComponent>()
{
	for (auto component : m_components)
	{
		if (component->getComponentTypeName() == "TransformComponent")
			return (TransformComponent*)component;
	}
	return nullptr;
}

template<>
RenderComponent* Entity::getComponent<RenderComponent>()
{
	for (auto component : m_components)
	{
		if (component->getComponentTypeName() == "RenderComponent")
			return (RenderComponent*)component;
	}
	return nullptr;
}

template<>
bool Entity::removeComponent<TransformComponent>()
{
	auto iter = m_components.begin();
	while (iter != m_components.end())
	{
		Component* component = *iter;
		if (component->getComponentTypeName() == "TransformComponent")
		{
			m_components.erase(iter);
			return true;
		}
	}
	return false;
}

template<>
bool Entity::removeComponent<RenderComponent>()
{
	auto iter = m_components.begin();
	while (iter != m_components.end())
	{
		Component* component = *iter;
		if (component->getComponentTypeName() == "RenderComponent")
		{
			m_components.erase(iter);
			return true;
		}
	}
	return false;
}

template<>
bool Entity::applyComponent<TransformComponent>()
{
	if (getComponent<TransformComponent>())
		return false;
	m_components.push_back(new TransformComponent());
	return true;
}

template<>
bool Entity::applyComponent<RenderComponent>()
{
	if (getComponent<RenderComponent>())
		return false;
	m_components.push_back(new RenderComponent());
	return true;
}

void Entity::setParent_implement(Instance* instance)
{
	if (!instance||instance->getInstanceType() == "Scene")
	{
		setRoot(true);
	}
	else
	{
		setRoot(false);
	}
}
