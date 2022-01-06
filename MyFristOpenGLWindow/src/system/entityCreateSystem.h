#pragma once
#include "system.h"
class EntityCreateSystem final:
    public System
{
private:
	enum class Commond
	{
		_Box = 1
	};
public:
	virtual int getOrder()
	{
		return 4000;
	}
	virtual uint16_t getSystemType()
	{
		return 3;
	}
protected:
	virtual void execute_implement();
private:
	template<uint16_t option>
	void exe(std::string exeCommand) {}

	template<>
	void exe<1>(std::string exeCommand);
};

