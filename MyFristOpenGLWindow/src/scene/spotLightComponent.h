#pragma once
#include "component.h"
#include <common/coordinateType.h>
class SpotLightComponent :
    public Component
{
public:
    virtual std::string getComponentTypeName()
    {
        return "SpotLightComponent";
    }
    void setAmbient(Vector3 ambient)
    {
        m_ambient = ambient;
    }
    Vector3 getAmbient()
    {
        return m_ambient;
    }

    void setDiffuse(Vector3 diffuse)
    {
        m_diffuse = diffuse;
    }
    Vector3 getDiffuse()
    {
        return m_diffuse;
    }

    void setSpecular(Vector3 specular)
    {
        m_specular = specular;
    }
    Vector3 getSpecular()
    {
        return m_specular;
    }

    void setCutOff(float cutOff)
    {
        m_cutOff = cutOff;
    }
    float getCutOff()
    {
        return m_cutOff;
    }
private:
    Vector3 m_ambient = { 1,1,1 };
    Vector3 m_diffuse = { 1,1,1 };
    Vector3 m_specular = { 1,1,1 };

    float m_cutOff = glm::cos(glm::radians(12.5f));
};

