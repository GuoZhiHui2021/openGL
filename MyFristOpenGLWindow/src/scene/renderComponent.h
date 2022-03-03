#pragma once
#include "component.h"
#include <common/coordinateType.h>
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
    void setOutline(bool outline)
    {
        m_isOutline = outline;
    }
    bool getOutline()
    {
        return m_isOutline;
    }
    void setOutlineColor(Vector3 color)
    {
        m_outlineColor = color;
    }
    Vector3 getOutlineColor()
    {
        return m_outlineColor;
    }
    void setOutlineWidth(float width)
    {
        m_outlineWidth = width;
    }
    float getOutlineWidth()
    {
        return m_outlineWidth;
    }
    void setCullFace(unsigned int cullFace)
    {
        cullFace &= 0XF;
        m_cullFace = cullFace;
    }
    unsigned int getCullFace()
    {
        return m_cullFace;
    }
private:
    bool m_visible;
    bool m_world_visible;
    std::string m_material;
    std::string m_mesh = "Box";
    bool m_isOutline = false;
    Vector3 m_outlineColor = {1,1,1};
    float m_outlineWidth = 1.0f;
    unsigned int m_cullFace = 1;
    
};

