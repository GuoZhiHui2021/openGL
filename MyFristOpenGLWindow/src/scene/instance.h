#pragma once
#include  <vector>
#include <string>
class Instance
{
public:
	Instance();
	~Instance();
	int64_t getInstanceId()
	{
		return m_instance_id;
	}
	std::vector<Instance*> getChildren()
	{
		return m_children;
	}
	void addChild(Instance* instance);
	void removeChild(int64_t uid);
	Instance* getParent()
	{
		return m_parent;
	}
	bool isRoot()
	{
		return m_isRoot;
	}
	Instance* getRootParent()
	{
		Instance* parent = getParent();
		if (!parent || m_isRoot)
		{
			return this;
		}
		return parent->getRootParent();
	}

	virtual std::string getInstanceType()
	{
		return "Instance";
	}
protected:
	void setParent(Instance* parent);
	virtual void setParent_implement(Instance* parent);
	void setRoot(bool root)
	{
		m_isRoot = root;
	}
private:
	Instance* m_parent;
	bool m_isRoot;
	int64_t m_instance_id;
protected:
	std::vector<Instance*> m_children;
};

