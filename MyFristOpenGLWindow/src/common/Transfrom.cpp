#include "Transfrom.h"

Transfrom::Transfrom() :m_trans(1.0f)
{

}

Transfrom::Transfrom(const Transfrom& transform) : Transfrom()
{
	m_trans = transform.m_trans;
}

Transfrom::Transfrom(const glm::mat4 n_mat4) : Transfrom()
{
	m_trans = n_mat4;
}

Transfrom::~Transfrom()
{
}

Transfrom Transfrom::rotate(float angle, glm::vec3 axis) const
{
	return Transfrom(glm::rotate(m_trans, angle, axis));
}

Transfrom Transfrom::translate(glm::vec3 vector) const
{
	return Transfrom(glm::translate(m_trans, vector));
}

Transfrom Transfrom::scale(glm::vec3 n_scale) const
{
	return Transfrom(glm::scale(m_trans, n_scale));
}

void* Transfrom::value() const
{
	return (void*)glm::value_ptr(m_trans);
}