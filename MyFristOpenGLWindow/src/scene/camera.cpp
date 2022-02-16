#include "camera.h"
#include <render/def.h>
Camera::Camera():\
	m_cameraPos(0,0,-3), m_cameraFront(0,0,1), m_cameraUp(0,1,0),\
	m_view_x(DEFAULT_CAMERA_VEIW_X), m_view_y(DEFAULT_CAMERA_VEIW_Y),\
	m_view_x_offset(DEFAULT_CAMERA_VEIW_X_OFFSET),m_view_y_offset(DEFAULT_CAMERA_VEIW_Y_OFFSET)
{
}

void Camera::setView(Vector3 pos, Vector3 front, Vector3 up)
{
	m_cameraPos = pos;
	m_cameraFront = front;
	m_cameraUp = up;
	m_view_mat = LookAt(m_cameraPos, m_cameraFront, m_cameraUp);
}

Transfrom Camera::LookAt(Vector3 pos, Vector3 front, Vector3 up)
{
	Vector3 right = front * up * -1;
	glm::mat4 m = glm::mat4(glm::vec4(right.getVec3().x, right.getVec3().y, right.getVec3().z, 0.0f), \
			glm::vec4(up.getVec3().x, up.getVec3().y, up.getVec3().z, 0.0f), \
			glm::vec4(front.getVec3().x, front.getVec3().y, front.getVec3().z, 0.0f), \
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))\
		* glm::mat4(glm::vec4(0.0f, 0.0f, 0.0f, -1.0f * pos.getVec3().x), \
			glm::vec4(0.0f, 0.0f, 0.0f, -1.0f * pos.getVec3().y), \
			glm::vec4(0.0f, 0.0f, 0.0f, -1.0f * pos.getVec3().z), \
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	return Transfrom(m);
}

template<>
DirectionalLightComponent* Camera::getComponent<DirectionalLightComponent>()
{
	for (auto component : m_components)
	{
		if (component->getComponentTypeName() == "DirectionalLightComponent")
			return (DirectionalLightComponent*)component;
	}
	return nullptr;
}

template<>
PointLightComponent* Camera::getComponent<PointLightComponent>()
{
	for (auto component : m_components)
	{
		if (component->getComponentTypeName() == "PointLightComponent")
			return (PointLightComponent*)component;
	}
	return nullptr;
}

template<>
SpotLightComponent* Camera::getComponent<SpotLightComponent>()
{
	for (auto component : m_components)
	{
		if (component->getComponentTypeName() == "SpotLightComponent")
			return (SpotLightComponent*)component;
	}
	return nullptr;
}

template<>
bool Camera::removeComponent<DirectionalLightComponent>()
{
	auto iter = m_components.begin();
	while (iter != m_components.end())
	{
		Component* component = *iter;
		if (component->getComponentTypeName() == "DirectionalLightComponent")
		{
			m_components.erase(iter);
			return true;
		}
	}
	return false;
}

template<>
bool Camera::removeComponent<PointLightComponent>()
{
	auto iter = m_components.begin();
	while (iter != m_components.end())
	{
		Component* component = *iter;
		if (component->getComponentTypeName() == "PointLightComponent")
		{
			m_components.erase(iter);
			return true;
		}
	}
	return false;
}

template<>
bool Camera::removeComponent<SpotLightComponent>()
{
	auto iter = m_components.begin();
	while (iter != m_components.end())
	{
		Component* component = *iter;
		if (component->getComponentTypeName() == "SpotLightComponent")
		{
			m_components.erase(iter);
			return true;
		}
	}
	return false;
}

template<>
bool Camera::applyComponent<DirectionalLightComponent>()
{
	if (getComponent<DirectionalLightComponent>())
		return false;
	m_components.push_back(new DirectionalLightComponent());
	return true;
}

template<>
bool Camera::applyComponent<PointLightComponent>()
{
	if (getComponent<PointLightComponent>())
		return false;
	m_components.push_back(new PointLightComponent());
	return true;
}

template<>
bool Camera::applyComponent<SpotLightComponent>()
{
	if (getComponent<SpotLightComponent>())
		return false;
	m_components.push_back(new SpotLightComponent());
	return true;
}
