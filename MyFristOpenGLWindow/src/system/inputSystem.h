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
private:
	enum class Commond
	{
		_Front = 1,
		_Right = 2,
		_Yaw = 3,
		_Pitch = 4,
	};
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
private:
	int m_right = 0;
	int m_front = 0;
	int m_yaw = 0;
	int m_pitch = 0;
};

