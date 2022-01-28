#include "inputSystem.h"
#include <render/glWindow.h>
#include <GLFW/glfw3.h>
#include <scene/cameraManager.h>
#include <scene/sceneManager.h>
#include "systemManager.h"
#include <scene/transformComponent.h>

void InputSystem::execute_implement()
{
	std::unordered_map<int, int> inputEvents = getInputEvent();
	clearInputEvent();
	
	for (auto iter : inputEvents)
	{
		switch (iter.first)
		{
		default:
			break;
		case (GLFW_KEY_W):m_front += iter.second; break;
		case (GLFW_KEY_S):m_front -= iter.second; break;
		case (GLFW_KEY_A):m_right -= iter.second; break;
		case (GLFW_KEY_D):m_right += iter.second; break;
		case (MOUSE_UP):m_yaw += iter.second; break;
		case (MOUSE_RIGHT):m_pitch += iter.second; break;
		}
	}
	uint64_t cameraId = CameraManager::Instance()->getMainCameraId();
	Scene* scene = SceneManager::Instance()->getCurScene();
	if (scene && scene->getEntity(cameraId) && scene->getEntity(cameraId)->getInstanceType() == "Camera"&& scene->getEntity(cameraId) -> getComponent<TransformComponent>())
	{
		TransformComponent* t = scene->getEntity(cameraId)->getComponent<TransformComponent>();
		if (m_front != 0 || m_right != 0)
		{
			char commandStr[127];
			sprintf_s(commandStr, "{%llu,%d,%d}", cameraId, m_front, m_right);
			SystemManager::Instance()->pushSystemCommand(SystemCommand(9, 1, commandStr));
		}
		if (m_yaw != 0 || m_pitch != 0)
		{
			char commandStr[127];
			sprintf_s(commandStr, "{%llu,%d,%d}", cameraId, m_yaw, m_pitch);
			SystemManager::Instance()->pushSystemCommand(SystemCommand(9, 2, commandStr));
		}
	}
	m_front = 0;
	m_right = 0;
	m_yaw = 0;
	m_pitch = 0;
}
