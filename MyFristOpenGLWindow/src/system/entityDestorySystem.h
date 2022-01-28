#pragma once
#include "system.h"
class EntityDestorySystem final:
    public System
{
public:
	virtual int getOrder()
	{
		return 10000;
	}
	virtual uint16_t getSystemType()
	{
		return 8;
	}
protected:
    virtual void execute_implement();
    void destory(std::string data);
	void destory(Entity* entity);
private:

};

