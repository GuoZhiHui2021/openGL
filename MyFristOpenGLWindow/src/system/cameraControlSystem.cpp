#include "cameraControlSystem.h"
#include <scene/sceneManager.h>
#include <scene/cameraManager.h>
#include "systemManager.h"
#include <common/fileUtil.h>
#include <common/util.h>
#include <scene/world.h>

void CameraControlSystem::execute_implement()
{
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_Offset:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_OrientationOffset:exe<2>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_AspectOffset:exe<3>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_Size:exe<4>(m_commands[i].m_data); break;
		default:
			break;
		}
	}
}

template<>
void CameraControlSystem::exe<1>(std::string exeCommand)
{
	Scene* scene = SceneManager::Instance()->getCurScene();
	if (scene)
	{
		int64_t id = 0;
		std::vector<int> offset;
		if (getIntV2Value(exeCommand.c_str(), id, offset) && id > 0 && id == CameraManager::Instance()->getMainCameraId())
		{
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				float speed = CameraManager::Instance()->getCameraSpeed();
				auto interval = World::Instance()->getTickInterval();
				TransformComponent* component = scene->getEntity(id)->getComponent<TransformComponent>();
				Transfrom t = component->getWorldTransfrom();
				Transfrom nt = t.translate(glm::vec3(offset[1] * speed * interval/1000.0f, 0, offset[0] * speed * interval / 1000.0f));
				Vector3 p = component->getPosition();
				char commandStr[127];
				sprintf_s(commandStr, "{%llu,%f,%f,%f}", id, nt[3].x, nt[3].y, nt[3].z);
				SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, commandStr));
			}
		}
	}
}

template<>
void CameraControlSystem::exe<2>(std::string exeCommand)
{
	Scene* scene = SceneManager::Instance()->getCurScene();
	if (scene)
	{
		int64_t id = 0;
		std::vector<int> offset;
		if (getIntV2Value(exeCommand.c_str(), id, offset) && id > 0 && id == CameraManager::Instance()->getMainCameraId())
		{
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				float speed = CameraManager::Instance()->getCameraAngularSpeed();
				auto interval = World::Instance()->getTickInterval();
				TransformComponent* component = scene->getEntity(id)->getComponent<TransformComponent>();
				//Transfrom t = component->getTransfrom();
				Vector3 r = component->getRotation();
				/*Transfrom t = Transfrom().rotate(angleToRadian(r.getVec3().x), angleToRadian(r.getVec3().y), angleToRadian(r.getVec3().z));
				Transfrom nt = t.rotate(angleToRadian(offset.getVec3().x), 0, angleToRadian(offset.getVec3().z));*/
				float x = r.getVec3().x + (float)(offset[0]) / 1000.0f * speed * interval / 1000.0f;
				float y = r.getVec3().y + (float)(offset[1]) / 1000.0f * speed * interval / 1000.0f;
				x = x < -89.0f ? -89.0f : x>89.0f ? 89.0f:x;
				char commandStr[127];
				sprintf_s(commandStr, "{%llu,%f,%f,%f}", id, x, y, 0.0f);
				SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, commandStr));
			}
		}
	}
}

template<>
void CameraControlSystem::exe<3>(std::string exeCommand)
{
	Scene* scene = SceneManager::Instance()->getCurScene();
	if (scene)
	{
		int64_t id = 0;
		int iAspect;
		float aspect;
		if (getIntValue(exeCommand.c_str(), id, iAspect) && id > 0 && id == CameraManager::Instance()->getMainCameraId())
		{
			aspect = iAspect / 1000.0f;
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				CameraManager::Instance()->setAspect(CameraManager::Instance()->getAspect() + aspect);
			}
		}
	}
}

template<>
void CameraControlSystem::exe<4>(std::string exeCommand)
{
	Scene* scene = SceneManager::Instance()->getCurScene();
	if (scene)
	{
		int64_t id = 0;
		std::vector<int> value;
		if (getIntV2Value(exeCommand.c_str(), id, value) && id > 0 && id == CameraManager::Instance()->getMainCameraId())
		{
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				CameraManager::Instance()->setViewSize(value[0], value[1]);
			}
		}
	}
}
