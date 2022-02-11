#pragma once
#include "instance.h"
#include "component.h"
#include "transformComponent.h"
#include "renderComponent.h"
#include "directionalLightComponent.h"
#include "pointLightComponent.h"
#include "spotLightComponent.h"
#include <common/coordinateType.h>
#include <vector>
class Entity :public Instance
{
public:
	Entity() :m_dirty(true), m_static(false), m_sustained(false), m_uniform_id(0)
	{

	}
	~Entity();

	virtual std::string getInstanceType()
	{
		return "Entity";
	}
	void setUniformId(uint16_t id)
	{
		m_uniform_id = id;
	}
	uint16_t getUniformId()
	{
		return m_uniform_id;
	}
	void setDirty(bool dirty)
	{
		m_dirty = dirty;
	}
	bool getDirty()
	{
		return m_dirty;
	}

	template<class T>
	T* getComponent()
	{
		return nullptr;
	}

	template<>
	TransformComponent* getComponent<TransformComponent>();

	template<>
	RenderComponent* getComponent<RenderComponent>();

	template<>
	DirectionalLightComponent* getComponent<DirectionalLightComponent>();

	template<>
	PointLightComponent* getComponent<PointLightComponent>();

	template<>
	SpotLightComponent* getComponent<SpotLightComponent>();

	template<class T>
	bool removeComponent() { return false; }

	template<>
	bool removeComponent<TransformComponent>();

	template<>
	bool removeComponent<RenderComponent>();

	template<>
	bool removeComponent<DirectionalLightComponent>();

	template<>
	bool removeComponent<PointLightComponent>();

	template<>
	bool removeComponent<SpotLightComponent>();

	template<class T>
	bool applyComponent() { return false; }

	template<>
	bool applyComponent<TransformComponent>();

	template<>
	bool applyComponent<RenderComponent>();

	template<>
	bool applyComponent<DirectionalLightComponent>();

	template<>
	bool applyComponent<PointLightComponent>();

	template<>
	bool applyComponent<SpotLightComponent>();

	void setSustained(bool sustained)
	{
		m_sustained = sustained;
	}
	bool isSustained()
	{
		return m_sustained;
	}
	//virtual bool getRenderBuffer(void* vertices, unsigned int& verticesCount, void* elements, unsigned int& elementCounts) = 0;
	virtual void* getRenderVerticesBuffer(unsigned int& verticesCount) = 0;
	virtual void* getRenderElementsBuffer(unsigned int& elementCounts) = 0;
protected:
	virtual void setParent_implement(Instance* instance);
private:
	uint16_t m_uniform_id;
	bool m_dirty;
	bool m_static;
	bool m_sustained;
	std::vector<Component*> m_components;
};
