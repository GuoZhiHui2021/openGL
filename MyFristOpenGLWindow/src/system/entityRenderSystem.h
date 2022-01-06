#pragma once
#include "system.h"
class EntityRenderSystem final:
    public System
{
private:
    enum class Commond
    {
        _Visible = 1,
        _Material,
    };
public:
    virtual int getOrder()
    {
        return 8000;
    }
    virtual uint16_t getSystemType()
    {
        return 7;
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

    void updateRenderData(Entity* entity);
};

