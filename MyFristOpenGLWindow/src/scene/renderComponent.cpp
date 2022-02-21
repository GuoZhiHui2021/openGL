#include "renderComponent.h"
#include <render/materialManager.h>
#include <render/renderManager.h>
#include <render/meshManager.h>
bool RenderComponent::setMaterial(std::string material)
{
	if (material == m_material)
		return false;
	Material* materialInstance = MaterialManager::Instance()->getOrCreateMaterial(material);
	if (!materialInstance)
		return false;
	m_material = material;
	return true;
}

std::string RenderComponent::getMaterial()
{
	return m_material;
}

void RenderComponent::setMesh(std::string mesh)
{
	MeshNodeInstance* m = MeshManager::Instance()->getOrCreateMesh(mesh);
	if (m)
	{
		m_mesh = mesh;
	}
}

