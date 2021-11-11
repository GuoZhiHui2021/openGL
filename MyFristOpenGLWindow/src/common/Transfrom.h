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
	void* value() const;

private:
	glm::mat4 m_trans;

};


