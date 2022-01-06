#pragma once
#include <common/singleton.h>
#include <queue>
#include <functional>
#include "system.h"

class SystemManager:public Singleton<SystemManager>
{
public:
	SystemManager();
	~SystemManager();
	void add(System* sys);
	void pushSystemCommand(SystemCommand _commond);
	void tick();
private:
	System* getSystem(uint16_t type);
private:
	struct cmp
	{
		bool operator()(System* A, System* B)
		{
			return A->getOrder() < B->getOrder();
		}
	};
	cmp m_cmp;
private:
	std::vector<System*> m_system;
	std::vector<SystemCommand> m_commonds;
};

