#pragma once
#include <common/singleton.h>
#include <render/render.h>
#include <string>
#include <scene/entity.h>
#include <unordered_set>
class RenderManager:public Singleton<RenderManager>
{
public:
	//RenderData* getOrCreateRenderData(Entity* entity);
	void updateRenderData(RenderData* data);
	Render* getOrCreateRender(std::string prototype);
	bool destory(int64_t entityId);
	bool hasRenderData(int64_t entityId);
	void clearLights()
	{
		m_directionalLightDatas.clear();
		m_pointLightDatas.clear();
		m_spotLightDatas.clear();
	}
	void addDirectionalLightData(DirectionalLightData data)
	{
		m_directionalLightDatas.push_back(data);
	}
	void addPointLightData(PointLightData data)
	{
		m_pointLightDatas.push_back(data);
	}
	void addSpotLightData(SpotLightData data)
	{
		m_spotLightDatas.push_back(data);
	}
	std::vector<DirectionalLightData> getDirectionalLightDatas()
	{
		return m_directionalLightDatas;
	}
	std::vector<PointLightData> getPointLightData()
	{
		return m_pointLightDatas;
	}
	std::vector<SpotLightData> getSpotLightData()
	{
		return m_spotLightDatas;
	}
	void update();
private:
	bool add(RenderData* data);
	bool singleRender(int64_t id);
private:
	std::unordered_map<int64_t, RenderData*> m_renderDatas;
	std::unordered_set<int64_t> m_singleRenderDatas;
	std::unordered_map<std::string, Render*> m_renders;
	std::vector<DirectionalLightData> m_directionalLightDatas;
	std::vector<PointLightData> m_pointLightDatas;
	std::vector<SpotLightData> m_spotLightDatas;
};

