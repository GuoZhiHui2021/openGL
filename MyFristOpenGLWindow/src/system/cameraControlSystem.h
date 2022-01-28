#pragma once
#include "system.h"
class CameraControlSystem final:
    public System
{
private:
	enum class Commond
	{
		_Offset = 1,
		_OrientationOffset = 2
	};
public:
	virtual int getOrder()
	{
		return 9000;
	}
	virtual uint16_t getSystemType()
	{
		return 9;
	}
protected:
	virtual void execute_implement();
private:
	template<uint16_t option>
	void exe(std::string exeCommand) {}

	template<>
	void exe<1>(std::string exeCommand);

	template<>
	void exe<2>(std::string exeCommand);
};

