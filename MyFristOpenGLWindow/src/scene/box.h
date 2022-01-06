#pragma once
#include "entity.h"
#include <string>
class Box:public Entity
{
public:
	Box();
	virtual std::string getInstanceType()
	{
		return "Box";
	}
	//virtual bool getRenderBuffer(void* vertices, unsigned int& verticesCount, void* elements, unsigned int& elementCounts);
	virtual void* getRenderVerticesBuffer(unsigned int& verticesCount);
	virtual void* getRenderElementsBuffer(unsigned int& elementCounts);
private:

	const Vector3 m_vposition[8] = { Vector3(-0.5f,-0.5f,-0.5f),Vector3(0.5f,-0.5f,-0.5f),Vector3(-0.5f,0.5f,-0.5f),Vector3(0.5f,0.5f,-0.5f),Vector3(-0.5f,-0.5f,0.5f),Vector3(0.5f,-0.5f,0.5f),Vector3(-0.5f,0.5f,0.5f),Vector3(0.5f,0.5f,0.5f) };
	const uint8_t m_indices[36] = { 1,0,3,0,2,3,3,2,7,2,6,7,4,5,6,5,7,6,4,5,0,5,1,0,0,4,2,4,6,2,5,1,7,1,3,7 };
	const float m_uv[12] = { 0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f };
	float m_alpha = 1.0f;
	float m_color[3] = { 1.0f,1.0f,1.0f };
};

