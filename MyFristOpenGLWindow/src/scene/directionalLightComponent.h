#pragma once
#include "component.h"
#include <common/coordinateType.h>
class DirectionalLightComponent :
    public Component
{
public:
    virtual std::string getComponentTypeName()
    {
        return "DirectionalLightComponent";
    }
    void setDirection(Vector3 direction)
    {
        m_direction = direction;
    }
    Vector3 getDirection()
    {
        return m_direction;
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

private:
    Vector3 m_direction = { 0,0.70710678,0.70710678 };
    Vector3 m_ambient = { 1,1,1 };//环境光
    Vector3 m_diffuse = { 1,1,1 };//漫反射
    Vector3 m_specular = { 1,1,1 };//镜面反射
};

