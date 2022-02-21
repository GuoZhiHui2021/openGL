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


