#pragma once
#include "instance.h"
#include <string>
class Component
{
public:
    Component();
    int64_t getInstanceId()
    {
        return m_instance_id;
    }
    virtual std::string getComponentTypeName()
    {
        return "Component";
    }
protected:
    Instance* m_entity;
    int64_t m_instance_id;
};

