#pragma once
#include "component.h"
#include <string>
class MeshNodeInstance;
class RenderComponent :
    public Component
{
public:
    RenderComponent() :m_visible(true), m_world_visible(true), m_material("")
    {}
    virtual std::string getComponentTypeName()
    {
        return "RenderComponent";
    }
    bool setMaterial(std::string material);
    std::string getMaterial();
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
    void setMesh(std::string);
    std::string getMesh()
    {
        return m_mesh;
    }
private:
    bool m_visible;
    bool m_world_visible;
    std::string m_material;
    std::string m_mesh = "Box";
    
};

