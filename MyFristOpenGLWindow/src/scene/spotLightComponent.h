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
        m_cutOff = glm::cos(glm::radians(cutOff));
    }
    float getCutOff()
    {
        return m_cutOff;
    }
    void setOutCutOff(float outCutOff)
    {
        m_outCutOff = glm::cos(glm::radians(outCutOff));
    }
    float getOutCutOff()
    {
        return m_outCutOff;
    }
    void setStrength(float strength)
    {
        m_strength = strength;
    }
    float getStrength()
    {
        return m_strength;
    }
private:
    Vector3 m_ambient = { 0,0,0 };
    Vector3 m_diffuse = { 0.8,0.8,0.8 };
    Vector3 m_specular = { 1,1,1 };

    float m_cutOff = glm::cos(glm::radians(12.5f));
    float m_outCutOff = glm::cos(glm::radians(17.5f));
    float m_strength = 0.8f;
};

