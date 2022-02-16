#pragma once
#include <common/singleton.h>
#include <common/coordinateType.h>
#include <vector>

#define MAX_ASPECT 45.0f
#define MIN_ASPECT 1.0f
class CameraManager :
    public Singleton<CameraManager>
{
public:
    Transfrom getViewTransfrom();

    Vector3 getMainCameraPosition();

    Vector3 getMainCameraDirection();

    Transfrom calculate_lookAt_matrix(Vector3 position, Vector3 front);

    Transfrom getPerspectiveTransfrom();

    void addCamera(uint64_t id);
    
    void deleteCamera(uint64_t id);
    
    void setMainCamera(uint64_t id);
    
    uint64_t getMainCameraId();

    float getCameraSpeed()
    {
        return m_cameraSpeed;
    }
    void setCameraSpeed(float speed)
    {
        m_cameraSpeed = speed;
    }
    float getCameraAngularSpeed()
    {
        return m_cameraAngularSpeed;
    }
    void setCameraAngularSpeed(float speed)
    {
        m_cameraAngularSpeed = speed;
    }
    void setAspect(float aspect);
    float getAspect()
    {
        return m_aspect;
    }
    void setViewSize(int width,int height)
    {
        m_viewWidth = width;
        m_viewHeight = height;
        setDirty();
    }
    void setDirty()
    {
        m_viewTransfromDirty = true;
        m_cameraPositionDirty = true;
        m_cameraDirectionDirty = true;
    }
private:
    float m_cameraSpeed = 2.0f;
    float m_cameraAngularSpeed = 3.0f;
    float m_aspect = 45.0f;
    float m_viewWidth = 800.0f;
    float m_viewHeight = 600.0f;
    float m_near = 0.1f;
    float m_far = 100.0f;
    uint64_t mMainCameraId = 0;
    std::vector<uint64_t> mCamerasId;
    bool m_viewTransfromDirty = true;
    bool m_cameraPositionDirty = true;
    bool m_cameraDirectionDirty = true;
    Transfrom m_viewTransfrom;
    Transfrom m_perspectiveTransfrom;
    Vector3 m_cameraPosition;
    Vector3 m_cameraDirection;
};

