#pragma once
#include "system.h"

enum class InputSystemOptionType
{
	_SCENE = 1,
	_ENTITY_CREATE,
	_ENTITY_TRANSFORM,
	_ENTITY_RENDER,
	_ENTITY_DESTORY,
	_END,
};
class InputSystem final:
    public System
{
public:
	virtual int getOrder()
	{
		return 100;
	}
	virtual uint16_t getSystemType()
	{
		return 1;
	}
protected:
    virtual void execute_implement();
};

