#pragma once
#include "system.h"
#include <unordered_set>
class EntityTransformSystem final:
    public System
{
private:
    enum class Commond
    {
        _Velocity = 1,
        _AngularVelocity,
        _Position,
        _Rotation,
        _Size,
    };
public:
    virtual int getOrder()
    {
        return 6000;
    }
    virtual uint16_t getSystemType()
    {
        return 6;
    }
protected:
    virtual void execute_implement();
private:
    template<uint16_t option>
    void exe(std::string exeCommand){}

    template<>
    void exe<1>(std::string exeCommand);
    template<>
    void exe<2>(std::string exeCommand);
    template<>
    void exe<3>(std::string exeCommand);
    template<>
    void exe<4>(std::string exeCommand);
    template<>
    void exe<5>(std::string exeCommand);
private:
    std::unordered_set<int64_t> m_positioned;
    std::unordered_set<int64_t> m_rotationed;
    std::unordered_set<int64_t> m_changes;
};

