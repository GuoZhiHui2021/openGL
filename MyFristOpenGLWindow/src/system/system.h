#pragma once
#include <string>
#include <vector>
#include <scene/entity.h>
enum class SystemCommandType
{
	SCENE = 1,
	ENTITY_CREATE,
	ENTITY_RELATION,
	ENTITY_COMPONENT,
	ENTITY_TRANSFORM,
	ENTITY_RENDER,
	ENTITY_DESTORY,
	END = 8,
};
struct SystemCommand
{
	uint16_t m_type = 0;
	uint16_t m_option = 0;
	std::string m_data;
	SystemCommand(uint16_t type, uint16_t option, std::string data)
	{
		m_type = type;
		m_option = option;
		m_data = data;
	}
};
class System
{
public:
	void execute()
	{
		execute_implement();
		m_commands.clear();
	}
	void pushCommand(SystemCommand data)
	{
		if (data.m_type > 0 && data.m_type == getSystemType())
			m_commands.push_back(data);
	}
	virtual uint16_t getSystemType()
	{
		return 0;
	}
	virtual int getOrder() = 0;
protected:
	virtual void execute_implement()
	{

	}
	Entity* getEntity(int64_t id);
protected:
	std::vector<SystemCommand> m_commands;
};

