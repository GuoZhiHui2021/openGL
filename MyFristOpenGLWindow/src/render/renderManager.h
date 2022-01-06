#pragma once
#include <common/singleton.h>
#include <render/render.h>
#include <string>
#include <scene/entity.h>
class RenderManager:public Singleton<RenderManager>
{
public:
	//RenderData* getOrCreateRenderData(Entity* entity);
	void updateRenderData(RenderData* data);
	Render* getOrCreateRender(std::string prototype);
	bool destory(int64_t entityId);
	bool hasRenderData(int64_t entityId);
	void update();
private:
	bool add(RenderData* data);
private:
	std::unordered_map<int64_t, RenderData*> m_renderDatas;
	std::unordered_map<std::string, Render*> m_renders;
};

