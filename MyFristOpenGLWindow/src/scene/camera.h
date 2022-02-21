#pragma once
#include "entity.h"
class Camera :
    public Entity
{
public:
    Camera();
    virtual std::string getInstanceType()
    {
        return "Camera";
    }

    void setView(Vector3 pos, Vector3 front, Vector3 up);
    Transfrom LookAt(Vector3 pos, Vector3 front, Vector3 up);
    Transfrom getViewMat()
    {
        return m_view_mat;
    }
private:
    Vector3 m_cameraPos;
    Vector3 m_cameraFront;
    Vector3 m_cameraUp;
    Transfrom m_view_mat;
    float m_view_x;
    float m_view_y;
    float m_view_x_offset;
    float m_view_y_offset;
};

