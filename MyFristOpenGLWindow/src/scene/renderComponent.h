#pragma once
#include "component.h"
#include <string>
class RenderComponent :
    public Component
{
public:
    RenderComponent() :m_visible(true), m_world_visible(true), m_material("material/default.materialPrototype")
    {}
    virtual std::string getComponentTypeName()
    {
        return "RenderComponent";
    }
    bool setMaterial(std::string material);
    std::string getMaterial()
    {
        return m_material;
    }
    void setVisible(bool visible)
    {
        m_visible = visible;
    }
    bool getVisible()
    {
        return m_visible;
    }
    bool getWorldVisible()
    {
        return m_world_visible;
    }
private:
    bool m_visible;
    bool m_world_visible;
    std::string m_material;
    
};

