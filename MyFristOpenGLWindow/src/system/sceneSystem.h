#pragma once
#include "system.h"
class SceneSystem final:
    public System
{
private:
    enum class Commond
    {
        _Create = 1,
        _Switch,
        _Remove
    };
public:
	virtual int getOrder()
	{
		return 2000;
	}
    virtual uint16_t getSystemType()
    {
        return 2;
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
    template<>
    void exe<3>(std::string exeCommand);
};

