#pragma once
#include "component.h"
#include <common/coordinateType.h>
class TransformComponent :
    public Component
{
public:
	TransformComponent():m_drity(false),m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_size(1.0f, 1.0f, 1.0f), m_angularVelocity(0.0f,0.0f,0.0f),m_velocity(0.0f, 0.0f, 0.0f), m_transform(), m_world_transform()
	{};
	virtual std::string getComponentTypeName()
	{
		return "TransformComponent";
	}
	virtual void rotate(Vector3 vec);
	virtual void translate(Vector3 vec);
	virtual void scale(Vector3 vec);
	virtual void setPosition(Vector3 vec)
	{
		Vector3 offset = vec - m_position;
		translate(offset);
	}
	virtual void setRotation(Vector3 vec)
	{
		Vector3 offset = vec - m_rotation;
		rotate(offset);
	}
	virtual void setSize(Vector3 vec)
	{
		Vector3 offset = vec / m_size;
		scale(offset);
	}
	virtual void setVelocity(Vector3 vec)
	{
		m_velocity = vec;
	}
	virtual void setAngularVelocity(Vector3 vec)
	{
		m_angularVelocity = vec;
	}
	Vector3 getRotation()
	{
		return m_rotation;
	}
	Vector3 getPosition()
	{
		return m_position;
	}
	Vector3 getSize()
	{
		return m_size;
	}
	Vector3 getVelocity()
	{
		return m_velocity;
	}
	Vector3 getAngularVelocity()
	{
		return m_angularVelocity;
	}
	Transfrom getTransfrom();
	Transfrom getWorldTransfrom()
	{
		return m_world_transform;
	}
private:
	Transfrom m_transform;
	Transfrom m_world_transform;
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_size;
	Vector3 m_angularVelocity;
	Vector3 m_velocity;
	bool m_drity;
};
