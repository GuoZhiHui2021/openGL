#include "instance.h"
#include <common/util.h>
Instance::Instance():m_isRoot(false), m_parent(nullptr)
{
	m_instance_id = allocateId();
}

Instance::~Instance()
{
	for (auto iter : m_children)
	{
		delete(iter++);
	}
	m_children.clear();
}

void Instance::addChild(Instance* instance)
{
	if (!instance)
		return;
	if (Instance* parent = instance->getParent())
	{
		parent->removeChild(instance->getInstanceId());
	}
	m_children.push_back(instance);
	instance->setParent(this);
}

void Instance::removeChild(int64_t id)
{
	for (size_t i = 0; i < m_children.size(); i++)
	{
		if (m_children[i]->getInstanceId() == id)
		{
			Instance* child = m_children[i];
			m_children.erase(m_children.begin()+i);
			child:setParent(nullptr);
		}
	}
}

void Instance::setParent(Instance* parent)
{
	m_parent = parent;
	setParent_implement(parent);
}

void Instance::setParent_implement(Instance* parent)
{

}
