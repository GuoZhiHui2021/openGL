#include "coordinateType.h"
#define Minimum 0.000001f

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

Transfrom Transfrom::rotate(float x, float y, float z) const
{
	return rotate(z, glm::vec3(0, 0, 1)).rotate(x, glm::vec3(1, 0, 0)).rotate(y, glm::vec3(0, 1, 0));
}

Transfrom Transfrom::translate(glm::vec3 vector) const
{
	return Transfrom(glm::translate(m_trans, vector));
}

Transfrom Transfrom::scale(glm::vec3 n_scale) const
{
	return Transfrom(glm::scale(m_trans, n_scale));
}

Transfrom Transfrom::operator*(Transfrom transfrom) const
{
	return Transfrom(glm::mat4(m_trans) * transfrom.m_trans);
}

void* Transfrom::value()
{
	return (void*)glm::value_ptr(m_trans);
}

Vector3::Vector3():m_vec3(0.0f, 0.0f, 0.0f)
{
}

Vector3::Vector3(const Vector3& vec3): m_vec3(vec3.m_vec3)
{
}

Vector3::Vector3(const glm::vec3& vec3):m_vec3(vec3)
{
}

Vector3::Vector3(float x,float y,float z):m_vec3(x,y,z)
{
}

Vector3 Vector3::operator+(const Vector3& vec3) const
{
	return Vector3(m_vec3 + vec3.m_vec3);
}

Vector3 Vector3::operator-(const Vector3& vec3) const
{
	return Vector3(m_vec3 - vec3.m_vec3);
}

Vector3& Vector3::operator+=(const Vector3& vec3)
{
	m_vec3 = glm::vec3(m_vec3 + vec3.m_vec3);
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec3)
{
	m_vec3 = glm::vec3(m_vec3 - vec3.m_vec3);
	return *this;
}

Vector3 Vector3::operator*(const Vector3& vec3) const
{
	return Vector3(m_vec3 * vec3.m_vec3);
}

Vector3 Vector3::operator/(const Vector3& vec3) const
{
	return Vector3(m_vec3 / vec3.m_vec3);
}

Vector3& Vector3::operator*=(const Vector3& vec3)
{
	m_vec3 = glm::vec3(m_vec3 * vec3.m_vec3);
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& vec3)
{
	m_vec3 = glm::vec3(m_vec3 / vec3.m_vec3);
	return *this;
}

Vector3 Vector3::operator*(float scale) const
{
	return Vector3(m_vec3 * scale);
}

Vector3 Vector3::operator/(float scale) const
{
	return Vector3(m_vec3 / scale);
}

Vector3& Vector3::operator*=(float scale)
{
	m_vec3 = glm::vec3(m_vec3 * scale);
	return *this;
}

Vector3& Vector3::operator/=(float scale)
{
	m_vec3 = glm::vec3(m_vec3 / scale);
	return *this;
}

Vector3 Vector3::cross(Vector3 v)
{
	return Vector3(glm::cross(m_vec3, v.m_vec3));
}

Vector3 Vector3::normalize()
{
	return Vector3(glm::normalize(m_vec3));
}

bool Vector3::operator==(const Vector3& vec3)
{
	return  abs(m_vec3.x - vec3.m_vec3.x) < Minimum && abs(m_vec3.y - vec3.m_vec3.y) < Minimum && abs(m_vec3.z - vec3.m_vec3.z) < Minimum;
}

bool Vector3::operator!=(const Vector3& vec3)
{
	return !((*this)== vec3);
}

glm::vec3 Vector3::getVec3() const
{
	return glm::vec3(m_vec3);
}

void* Vector3::value() const
{
	return (void*)glm::value_ptr(m_vec3);
}

Vector2::Vector2():m_vec2(0.0f, 0.0f)
{
}

Vector2::Vector2(const Vector2& vec2): m_vec2(vec2.m_vec2)
{
}

Vector2::Vector2(const glm::vec2& vec2) : m_vec2(vec2)
{
}

Vector2::Vector2(float x, float y): m_vec2(x,y)
{
}

Vector2 Vector2::normalize()
{
	return Vector2(glm::normalize(m_vec2));
}

glm::vec2 Vector2::getVec2() const
{
	return m_vec2;
}

void* Vector2::value() const
{
	return (void*)glm::value_ptr(m_vec2);
}
