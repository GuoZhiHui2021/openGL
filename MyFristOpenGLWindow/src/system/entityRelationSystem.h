#pragma once
#include "system.h"
class EntityRelationSystem :
    public System
{
public:
	virtual int getOrder()
	{
		return 5000;
	}
	virtual uint16_t getSystemType()
	{
		return 5;
	}
protected:
    virtual void execute_implement();
};

