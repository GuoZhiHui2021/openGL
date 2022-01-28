#include "cameraControlSystem.h"
#include <scene/sceneManager.h>
#include <scene/cameraManager.h>
#include "systemManager.h"
#include <common/fileUtil.h>
#include <common/util.h>
bool getCameraOffsetValue(std::string str, int64_t& id, Vector3& offset)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 3)
		return false;
	int64_t t_id = 0;
	int t_front = 0;
	int t_right = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToInt(strs[1].c_str(), t_front) || !strToInt(strs[1].c_str(), t_right))
		return false;
	float speed = CameraManager::Instance()->getCameraSpeed();
	id = t_id;
	offset = Vector3((float)t_right * speed, 0, (float)t_front * speed);
	return true;
}
bool getCameraOrientationValue(std::string str, int64_t& id, Vector3& offset)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 3)
		return false;
	int64_t t_id = 0;
	int t_yaw = 0;
	int t_pitch = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToInt(strs[1].c_str(), t_yaw) || !strToInt(strs[2].c_str(), t_pitch))
		return false;
	float speed = CameraManager::Instance()->getCameraAngularSpeed();
	id = t_id;
	offset = Vector3((float)t_yaw / 1000.0f * speed, (float)t_pitch / 1000.0f * speed,0);
	return true;
}
void CameraControlSystem::execute_implement()
{
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_Offset:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_OrientationOffset:exe<2>(m_commands[i].m_data); break;
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
		Vector3 offset;
		if (getCameraOffsetValue(exeCommand.c_str(), id, offset) && id > 0 && id == CameraManager::Instance()->CameraManager::Instance()->getMainCameraId())
		{
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				TransformComponent* component = scene->getEntity(id)->getComponent<TransformComponent>();
				Vector3 p = component->getPosition();
				char commandStr[127];
				float x = p.getVec3().x + offset.getVec3().x;
				float z = p.getVec3().z + offset.getVec3().z;
				sprintf_s(commandStr, "{%llu,%f,%f,%f}", id, x, 0.0f, z);
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
		Vector3 offset;
		if (getCameraOrientationValue(exeCommand.c_str(), id, offset) && id > 0 && id == CameraManager::Instance()->CameraManager::Instance()->getMainCameraId())
		{
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				TransformComponent* component = scene->getEntity(id)->getComponent<TransformComponent>();
				Vector3 r = component->getRotation();
				float x = r.getVec3().x + offset.getVec3().x;
				float z = r.getVec3().z + offset.getVec3().z;
				char commandStr[127];
				sprintf_s(commandStr, "{%llu,%f,%f,%f}", id, offset.getVec3().x, offset.getVec3().y, offset.getVec3().z);
				SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, commandStr));
			}
		}
	}
}
