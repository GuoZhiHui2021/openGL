#include "cameraControlSystem.h"
#include <scene/sceneManager.h>
#include <scene/cameraManager.h>
#include "systemManager.h"
#include <common/fileUtil.h>
#include <common/util.h>
#include <scene/world.h>
bool getCameraOffsetValue(std::string str, int64_t& id, Vector3& offset)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 3)
		return false;
	int64_t t_id = 0;
	int t_front = 0;
	int t_right = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToInt(strs[1].c_str(), t_front) || !strToInt(strs[2].c_str(), t_right))
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

bool getCameraAspectValue(std::string str, int64_t& id, float& aspect)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	int t_aspect = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToInt(strs[1].c_str(), t_aspect))
		return false;
	id = t_id;
	aspect = t_aspect / 1000.0f;
	return true;
}
bool getCameraSizeValue(std::string str, int64_t& id, int& width, int& height)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 3)
		return false;
	int64_t t_id = 0;
	int t_width = 0;
	int t_height = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToInt(strs[1].c_str(), t_width)|| !strToInt(strs[2].c_str(), t_height))
		return false;
	id = t_id;
	width = t_width;
	height = t_height;
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
		Vector3 offset;
		if (getCameraOffsetValue(exeCommand.c_str(), id, offset) && id > 0 && id == CameraManager::Instance()->getMainCameraId())
		{
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				auto interval = World::Instance()->getTickInterval();
				TransformComponent* component = scene->getEntity(id)->getComponent<TransformComponent>();
				Transfrom t = component->getWorldTransfrom();
				Transfrom nt = t.translate(glm::vec3(offset.getVec3().x * interval/1000.0f, 0, offset.getVec3().z * interval / 1000.0f));
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
		Vector3 offset;
		if (getCameraOrientationValue(exeCommand.c_str(), id, offset) && id > 0 && id == CameraManager::Instance()->getMainCameraId())
		{
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				auto interval = World::Instance()->getTickInterval();
				TransformComponent* component = scene->getEntity(id)->getComponent<TransformComponent>();
				//Transfrom t = component->getTransfrom();
				Vector3 r = component->getRotation();
				/*Transfrom t = Transfrom().rotate(angleToRadian(r.getVec3().x), angleToRadian(r.getVec3().y), angleToRadian(r.getVec3().z));
				Transfrom nt = t.rotate(angleToRadian(offset.getVec3().x), 0, angleToRadian(offset.getVec3().z));*/
				float x = r.getVec3().x + offset.getVec3().x * interval / 1000.0f;
				float y = r.getVec3().y + offset.getVec3().y * interval / 1000.0f;
				x = x < -89.0f ? -89.0f : x>89.0f ? 89.0f:x;
				char commandStr[127];
				printf("x:%f,y:%f\n", x, y);
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
		float aspect;
		if (getCameraAspectValue(exeCommand.c_str(), id, aspect) && id > 0 && id == CameraManager::Instance()->getMainCameraId())
		{
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
		int width;
		int height;
		if (getCameraSizeValue(exeCommand.c_str(), id, width, height) && id > 0 && id == CameraManager::Instance()->getMainCameraId())
		{
			if (scene->getEntity(id) && scene->getEntity(id)->getInstanceType() == "Camera" && scene->getEntity(id)->getComponent<TransformComponent>())
			{
				CameraManager::Instance()->setViewSize(width, height);
			}
		}
	}
}
