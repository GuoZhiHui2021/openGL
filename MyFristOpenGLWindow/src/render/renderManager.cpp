#include "renderManager.h"
#include "materialManager.h"
#include <common/util.h>
#include <scene/renderComponent.h>

void RenderManager::updateRenderData(RenderData* data)
{
	RenderData* old_data = m_renderDatas.find(data->id) != m_renderDatas.end() ? m_renderDatas[data->id] : nullptr;
	if (old_data)
	{
		destory(old_data->id);
	}
	add(data);
}

Render* RenderManager::getOrCreateRender(std::string prototype)
{
	if (m_renders.find(prototype) != m_renders.end())
		return m_renders[prototype];
	MaterialPrototype* materialPrototype = MaterialManager::Instance()->getOrCreateMaterialPrototype(prototype);
	if (!materialPrototype)
		return nullptr;
	std::vector<MaterialPrototypeAttr> shaders = materialPrototype->getShaders();
	Render* render = new Render();
	render->initialize();
	for (auto shaderAttr : shaders)
	{
		if (!render->attachShader(shaderAttr.m_type, (char*)shaderAttr.m_value))
		{
			delete render;
			return nullptr;
		}
	}
	render->initialized();
	m_renders[prototype] = render;
	return render;
}

bool RenderManager::add(RenderData* data)
{
	if (!data)
		return false;
	auto iter = m_renderDatas.find(data->id);
	if (iter != m_renderDatas.end())
	{
		return false;
	}
	m_renderDatas[data->id] = data;
	Render* render = getOrCreateRender(data->prototype);
	if (!render)
		return false;
	//m_renders[data->prototype] = render;
	render->loadData(data);
	return true;
}

bool RenderManager::destory(int64_t entityId)
{
	if (m_renderDatas.find(entityId) != m_renderDatas.end())
	{
		RenderData* data = m_renderDatas[entityId];
		m_renderDatas.erase(entityId);
		if (m_renders.find(data->prototype) != m_renders.end())
		{
			m_renders[data->prototype]->deleteRenderData(entityId);
		}
		return true;
	}
	return false;
}

bool RenderManager::hasRenderData(int64_t entityId)
{
	if (m_renderDatas.find(entityId) != m_renderDatas.end())
	{
		return true;
	}
	return false;
}

void RenderManager::update()
{
	//todo sort
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	for (auto iter = m_renders.begin(); iter != m_renders.end(); iter++)
	{
		iter->second->render();
	}
	auto iter = m_renderDatas.begin();
	while (iter != m_renderDatas.end())
	{
		auto id = iter->first;
		iter++;
		destory(id);
	}
	clearLights();
}
