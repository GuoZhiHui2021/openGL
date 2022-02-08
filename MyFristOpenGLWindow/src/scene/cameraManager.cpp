#include "cameraManager.h"
#include "sceneManager.h"
#include "camera.h"
#include "transformComponent.h"
#include <common/util.h>

Transfrom CameraManager::getViewTransfrom()
{
    if (m_dirty)
    {
        if (Scene* scene = SceneManager::Instance()->getCurScene())
        {
            if (Camera* camera = static_cast<Camera*>(scene->getEntity(mMainCameraId)))
            {
                if (TransformComponent* component = camera->getComponent<TransformComponent>())
                {
                    Transfrom t = component->getWorldTransfrom();
                    Transfrom t2 = component->getTransfrom();
                    m_viewTransfrom = calculate_lookAt_matrix(Vector3(t[3].x, t[3].y, t[3].z), Vector3(-t2[2].x, -t2[2].y, -t2[2].z));
                }
                else
                {
                    m_viewTransfrom = Transfrom();
                }
            }
            else
            {
                m_viewTransfrom = Transfrom();
            }
        }
        else
        {
            m_viewTransfrom = Transfrom();
        }
        m_dirty = false;
    }  
    return m_viewTransfrom;
}

Transfrom CameraManager::calculate_lookAt_matrix(Vector3 position, Vector3 front)
{
    Vector3 zaxis = front.normalize() * -1;
    Vector3 xaxis = Vector3(0, 1, 0).cross(zaxis).normalize();
    Vector3 yaxis = zaxis.cross(xaxis);

    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -position.getVec3().x;
    translation[3][1] = -position.getVec3().y;
    translation[3][2] = -position.getVec3().z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.getVec3().x;
    rotation[1][0] = xaxis.getVec3().y;
    rotation[2][0] = xaxis.getVec3().z;
    rotation[0][1] = yaxis.getVec3().x;
    rotation[1][1] = yaxis.getVec3().y;
    rotation[2][1] = yaxis.getVec3().z;
    rotation[0][2] = zaxis.getVec3().x;
    rotation[1][2] = zaxis.getVec3().y;
    rotation[2][2] = zaxis.getVec3().z;

    return Transfrom(rotation * translation);
}

Transfrom CameraManager::getPerspectiveTransfrom()
{
    if (m_dirty)
    {
        m_perspectiveTransfrom = Transfrom(glm::perspective(glm::radians(m_aspect), m_viewWidth / m_viewHeight, m_near, m_far));
    }
    return m_perspectiveTransfrom;
}

void CameraManager::addCamera(uint64_t id)
{
    Scene* scene;
    if (!(scene = SceneManager::Instance()->getCurScene()))
        return;
    for (auto cid : mCamerasId)
    {
        if (cid == id)
            return;
    }
    if (scene->getEntity(id)->getInstanceType() == "Camera")
    {
        mCamerasId.push_back(id);
        if (!mMainCameraId)
            setMainCamera(id);
    }
}

void CameraManager::deleteCamera(uint64_t id)
{
    for (auto iter = mCamerasId.begin(); iter != mCamerasId.end(); iter++)
    {
        if (*iter == id)
        {
            if (mMainCameraId == id)
            {
                mMainCameraId = 0;
                setDirty();
            }
            mCamerasId.erase(iter);
            break;
        }
    }
}

void CameraManager::setMainCamera(uint64_t id)
{
    if (mMainCameraId == id)
        return;
    for (auto cid : mCamerasId)
    {
        if (cid == id)
        {
            mMainCameraId = id;
            setDirty();
            break;
        }
    }
}

uint64_t CameraManager::getMainCameraId()
{
    return mMainCameraId;
}

void CameraManager::setAspect(float aspect)
{
    m_aspect = aspect > MAX_ASPECT ? MAX_ASPECT : aspect < MIN_ASPECT ? MIN_ASPECT : aspect;
    setDirty();
}
