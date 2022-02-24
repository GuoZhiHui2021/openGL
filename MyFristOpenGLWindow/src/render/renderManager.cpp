#include "renderManager.h"
#include "materialManager.h"
#include <common/util.h>
#include <scene/renderComponent.h>
#include <render/def.h>
#define DEFAULT_RENDER (std::string("default"))
#define OUTLINE_RENDER (std::string("outline"))

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
	Render* render;
	if (OUTLINE_RENDER == materialPrototype->getRenderType())
	{
		render = new OutlineRender();
	}
	else
	{
		render = new Render();
	}
	if (!render)
		return nullptr;
	render->initialize();
	for (auto shaderAttr : shaders)
	{
		std::string a((char*)shaderAttr.m_value);
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
	bool toLoad = true;
	if (data->stencilRef & OUTLINE_STENCIL_MARK)
	{
		Render* outlineRender = getOrCreateRender("material/outline.materialPrototype");
		toLoad = false;
	}
	if(toLoad)
		render->loadData(data);
	else if (m_singleRenderDatas.find(data->id) == m_singleRenderDatas.end())
	{
		m_singleRenderDatas.insert(data->id);
	}
	
	return true;
}

bool RenderManager::singleRender(int64_t id)
{
	RenderData* data = m_renderDatas.find(id) == m_renderDatas.end() ? nullptr : m_renderDatas[id];
	if(!data)
		return false;
	{
		Render* defaultRender = getOrCreateRender(data->prototype);
		if (!defaultRender)
			return false;
		defaultRender->loadData(data);
		defaultRender->render();
		defaultRender->removeDatas();
	}
	{
		if (data->stencilRef & OUTLINE_STENCIL_MARK)
		{
			Render* outlineRender = getOrCreateRender("material/outline.materialPrototype");
			if (!outlineRender)
				return false;
			outlineRender->loadData(data);
			outlineRender->render();
			outlineRender->removeDatas();
		}
	}
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
			m_renders[data->prototype]->removeRenderData(entityId);
		}
		if (m_renders.find("material/outline.materialPrototype") != m_renders.end())
		{
			m_renders["material/outline.materialPrototype"]->removeRenderData(entityId);
		}
		delete data;
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
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
	for (auto iter = m_renders.begin(); iter != m_renders.end(); iter++)
	{
		iter->second->render();
		iter->second->removeDatas();
	}
	for (auto iter : m_singleRenderDatas)
	{
		singleRender(iter);
	}
	auto iter = m_renderDatas.begin();
	while (iter != m_renderDatas.end())
	{
		auto id = iter->first;
		iter++;
		destory(id);
	}
	m_singleRenderDatas.clear();
	clearLights();
}
