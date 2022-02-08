#include "inputSystem.h"
#include <render/glWindow.h>
#include <GLFW/glfw3.h>
#include <scene/cameraManager.h>
#include <scene/sceneManager.h>
#include "systemManager.h"
#include <scene/transformComponent.h>

void InputSystem::execute_implement()
{
	int right = 0;
	int front = 0;
	int yaw = 0;
	int pitch = 0;
	int srcoll = 0;
	int width = 0;
	int height = 0;
	std::unordered_map<int, int> inputEvents = getInputEvent();
	clearInputEvent();
	
	for (auto iter : inputEvents)
	{
		switch (iter.first)
		{
		default:
			break;
		case (GLFW_KEY_W):front -= iter.second; break;
		case (GLFW_KEY_S):front += iter.second; break;
		case (GLFW_KEY_A):right -= iter.second; break;
		case (GLFW_KEY_D):right += iter.second; break;
		case (MOUSE_UP):yaw += iter.second; break;
		case (MOUSE_RIGHT):pitch += iter.second; break;
		case (MOUSE_SRCOLL):srcoll += iter.second; break;
		case (WINDOW_WIDTH):width = iter.second; break;
		case (WINDOW_HEIGHT):height = iter.second; break;
		}
	}
	uint64_t cameraId = CameraManager::Instance()->getMainCameraId();
	Scene* scene = SceneManager::Instance()->getCurScene();
	if (scene && scene->getEntity(cameraId) && scene->getEntity(cameraId)->getInstanceType() == "Camera"&& scene->getEntity(cameraId) -> getComponent<TransformComponent>())
	{
		TransformComponent* t = scene->getEntity(cameraId)->getComponent<TransformComponent>();
		if (front != 0 || right != 0)
		{
			char commandStr[127];
			sprintf_s(commandStr, "{%llu,%d,%d}", cameraId, front, right);
			SystemManager::Instance()->pushSystemCommand(SystemCommand(9, 1, commandStr));
		}
		if (yaw != 0 || pitch != 0)
		{
			char commandStr[127];
			sprintf_s(commandStr, "{%llu,%d,%d}", cameraId, yaw, pitch);
			SystemManager::Instance()->pushSystemCommand(SystemCommand(9, 2, commandStr));
		}
		if (srcoll != 0)
		{
			char commandStr[127];
			sprintf_s(commandStr, "{%llu,%d}", cameraId, srcoll);
			SystemManager::Instance()->pushSystemCommand(SystemCommand(9, 3, commandStr));
		}
		if (width != 0 && height != 0)
		{
			char commandStr[127];
			sprintf_s(commandStr, "{%llu,%d,%d}", cameraId, width, height);
			SystemManager::Instance()->pushSystemCommand(SystemCommand(9, 4, commandStr));
		}
	}
}
