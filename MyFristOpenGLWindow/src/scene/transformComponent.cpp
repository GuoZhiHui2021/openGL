#include "transformComponent.h"
#include "entity.h"
#include <common/util.h>
#include <typeinfo>


void TransformComponent::rotate(Vector3 vec)
{
	m_rotation += vec;
	m_rotation = Vector3(angleToRadian(m_rotation.getVec3().x) * 180 / PI, \
		angleToRadian(m_rotation.getVec3().y) * 180 / PI, \
		angleToRadian(m_rotation.getVec3().z) * 180 / PI);
	m_drity = true;
}

void TransformComponent::translate(Vector3 vec)
{
	m_position += vec;
	m_drity = true;
}

void TransformComponent::scale(Vector3 vec)
{
	m_size *= vec;
	m_drity = true;
}

Transfrom TransformComponent::getTransfrom()
{
	if (m_drity)
	{
		m_transform = Transfrom().translate(m_position.getVec3()) \
			* Transfrom().rotate(angleToRadian(m_rotation.getVec3().z), glm::vec3(0, 0, 1)) \
			.rotate(angleToRadian(m_rotation.getVec3().x), glm::vec3(1, 0, 0)) 
			.rotate(angleToRadian(m_rotation.getVec3().y), glm::vec3(0, 1, 0)) \
			* Transfrom().scale(m_size.getVec3());
		m_drity = false;
	}
	return m_transform;
}
