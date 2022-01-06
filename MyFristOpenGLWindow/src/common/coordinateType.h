#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Transfrom
{
public:
	Transfrom();
	Transfrom(const Transfrom& transform);
	Transfrom(const glm::mat4 n_mat4);
	~Transfrom();

	Transfrom rotate(float angle, glm::vec3 axis) const;
	Transfrom translate(glm::vec3 vector) const;
	Transfrom scale(glm::vec3 n_scale) const;
	Transfrom operator * (Transfrom transfrom) const;
	void* value() const;

private:
	glm::mat4 m_trans;

};
class Vector3
{
public:
	Vector3();
	Vector3(const Vector3& vec3);
	Vector3(const glm::vec3& vec3);
	Vector3(float x,float y,float z);

	Vector3 operator + (const Vector3& vec3) const;
	Vector3 operator - (const Vector3& vec3) const;
	Vector3& operator += (const Vector3& vec3);
	Vector3& operator -= (const Vector3& vec3);
	Vector3 operator * (const Vector3& vec3) const;
	Vector3 operator / (const Vector3& vec3) const;
	Vector3& operator *= (const Vector3& vec3);
	Vector3& operator /= (const Vector3& vec3);
	Vector3 operator * (float scale) const;
	Vector3 operator / (float scale) const;
	Vector3& operator *= (float scale);
	Vector3& operator /= (float scale);
	bool operator==(const Vector3& vec3);
	bool operator!=(const Vector3& vec3);
	glm::vec3 getVec3() const;
	void* value() const;
private:
	glm::vec3 m_vec3;
};



