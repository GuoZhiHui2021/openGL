#pragma once
#include <common/singleton.h>
#include <common/coordinateType.h>
#include <vector>
class CameraManager :
    public Singleton<CameraManager>
{
public:
    Transfrom getViewTransfrom();

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
    
private:
    float m_cameraSpeed = 0.05f;
    float m_cameraAngularSpeed = 0.05f;
    uint64_t mMainCameraId = 0;
    std::vector<uint64_t> mCamerasId;
};

