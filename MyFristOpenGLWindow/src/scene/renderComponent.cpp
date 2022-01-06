#include "renderComponent.h"
#include <render/materialManager.h>
#include <render/renderManager.h>
bool RenderComponent::setMaterial(std::string material)
{
	if (material.empty())
		material = "material/default.material";
	if (material == m_material)
		return false;
	Material* materialInstance = MaterialManager::Instance()->getOrCreateMaterial(material);
	if (!materialInstance)
		return false;
	m_material = material;
	return true;
}

