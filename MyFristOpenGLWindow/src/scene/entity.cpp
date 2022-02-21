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

template<>
DirectionalLightComponent* Entity::getComponent<DirectionalLightComponent>()
{
	for (auto component : m_components)
	{
		if (component->getComponentTypeName() == "DirectionalLightComponent")
			return (DirectionalLightComponent*)component;
	}
	return nullptr;
}

template<>
PointLightComponent* Entity::getComponent<PointLightComponent>()
{
	for (auto component : m_components)
	{
		if (component->getComponentTypeName() == "PointLightComponent")
			return (PointLightComponent*)component;
	}
	return nullptr;
}

template<>
SpotLightComponent* Entity::getComponent<SpotLightComponent>()
{
	for (auto component : m_components)
	{
		if (component->getComponentTypeName() == "SpotLightComponent")
			return (SpotLightComponent*)component;
	}
	return nullptr;
}

template<>
bool Entity::removeComponent<DirectionalLightComponent>()
{
	auto iter = m_components.begin();
	while (iter != m_components.end())
	{
		Component* component = *iter;
		if (component->getComponentTypeName() == "DirectionalLightComponent")
		{
			m_components.erase(iter);
			return true;
		}
	}
	return false;
}

template<>
bool Entity::removeComponent<PointLightComponent>()
{
	auto iter = m_components.begin();
	while (iter != m_components.end())
	{
		Component* component = *iter;
		if (component->getComponentTypeName() == "PointLightComponent")
		{
			m_components.erase(iter);
			return true;
		}
	}
	return false;
}

template<>
bool Entity::removeComponent<SpotLightComponent>()
{
	auto iter = m_components.begin();
	while (iter != m_components.end())
	{
		Component* component = *iter;
		if (component->getComponentTypeName() == "SpotLightComponent")
		{
			m_components.erase(iter);
			return true;
		}
	}
	return false;
}

template<>
bool Entity::applyComponent<DirectionalLightComponent>()
{
	if (getComponent<DirectionalLightComponent>())
		return false;
	m_components.push_back(new DirectionalLightComponent());
	return true;
}

template<>
bool Entity::applyComponent<PointLightComponent>()
{
	if (getComponent<PointLightComponent>())
		return false;
	m_components.push_back(new PointLightComponent());
	return true;
}

template<>
bool Entity::applyComponent<SpotLightComponent>()
{
	if (getComponent<SpotLightComponent>())
		return false;
	m_components.push_back(new SpotLightComponent());
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
