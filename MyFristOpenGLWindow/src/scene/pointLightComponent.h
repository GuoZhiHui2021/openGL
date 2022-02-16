#pragma once
#include "component.h"
#include <common/coordinateType.h>
class PointLightComponent :
    public Component
{
public:
    virtual std::string getComponentTypeName()
    {
        return "PointLightComponent";
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

    void setConstant(float constant)
    {
        m_constant = constant;
    }
    float getConstant()
    {
        return m_constant;
    }

    void setLinear(float linear)
    {
        m_linear = linear;
    }
    float getLinear()
    {
        return m_linear;
    }

    void setQuadratic(float quadratic)
    {
        m_quadratic = quadratic;
    }
    float getQuadratic()
    {
        return m_quadratic;
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

    float m_constant = 1.0f;//常数项
    float m_linear = 0.09f;//一次项
    float m_quadratic = 0.032f;//二次项
    float m_strength = 0.8f;
};