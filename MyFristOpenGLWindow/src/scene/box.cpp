
#include "box.h"
#include <common/util.h>

Box::Box()
{

}

void* Box::getRenderVerticesBuffer(unsigned int& verticesCount)
{
	auto v = sizeof(m_indices);
	float* buffer = (float*)malloc(sizeof(m_indices) * 5 * sizeof(float));
	if (!buffer)
		return nullptr;
	for (size_t i = 0; i < sizeof(m_indices); i++)
	{
		Vector3 p = m_vposition[m_indices[i]];
		size_t u = i % 6 * 2;
		size_t v = u + 1;
		*(buffer + i * 5) = p.getVec3().x;
		*(buffer + i * 5 + 1) = p.getVec3().y;
		*(buffer + i * 5 + 2) = p.getVec3().z;
		*(buffer + i * 5 + 3) = m_uv[u];
		*(buffer + i * 5 + 4) = m_uv[v];
	}
	verticesCount = sizeof(m_indices);
	return buffer;
}

void* Box::getRenderElementsBuffer(unsigned int& elementCounts)
{
	unsigned int* buffer = (unsigned int*)malloc(36 * sizeof(unsigned int));
	if (!buffer)
		return nullptr;
	elementCounts = sizeof(m_indices);
	for (size_t i = 0; i < 36; i++)
	{
		*(buffer + i) = (unsigned int)i;
	}
	return buffer;
}


