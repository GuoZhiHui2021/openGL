#pragma once
#include "system.h"
class EntityComponentSystem :
    public System
{
	enum class Commond
	{
		_Add = 1,
		_Remove
	};
	enum class ComponentType
	{
		
		_TransformComponent = 1,
		_RenderComponent
	};
public:
	virtual int getOrder()
	{
		return 4500;
	}
	virtual uint16_t getSystemType()
	{
		return 4;
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

