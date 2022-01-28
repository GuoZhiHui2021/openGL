#include "cameraManager.h"
#include "sceneManager.h"
#include "camera.h"
#include "transformComponent.h"

Transfrom CameraManager::getViewTransfrom()
{
    if (Scene* scene = SceneManager::Instance()->getCurScene())
    {
        if (Camera* camera = static_cast<Camera*>(scene->getEntity(mMainCameraId)))
        {
            if (TransformComponent* component = camera->getComponent<TransformComponent>())
                return component->getWorldTransfrom();
        }
    }
    return Transfrom();
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
                mMainCameraId = 0;
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
            break;
        }
    }
}

uint64_t CameraManager::getMainCameraId()
{
    return mMainCameraId;
}
