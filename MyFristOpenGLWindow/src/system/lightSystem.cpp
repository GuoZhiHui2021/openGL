#include "lightSystem.h"
#include <common/fileUtil.h>
#include <common/util.h>

bool getV3Value(std::string str, int64_t& id, std::vector<float>& value)
{
	value.clear();
	value.resize(3, 0);
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 4)
		return false;
	int64_t t_id = 0;
	std::vector<float> t_value(3, 0);
	if (!strToInt64(strs[0].c_str(), t_id))
		return false;
	for (size_t i = 1; i < 4; i++)
	{
		if (!strToFloat(strs[i].c_str(), t_value[i - 1]))
			return false;
	}
	id = t_id;
	value.swap(t_value);
	return true;
}
bool getFloatValue(std::string str, int64_t& id, float& value)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	float t_value = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToFloat(strs[1].c_str(), t_value))
		return false;
	id = t_id;
	value = t_value;
	return true;
}

void LightSystem::execute_implement()
{
	for (size_t i = 0; i < m_commands.size(); i++)
	{
		uint16_t option = m_commands[i].m_option;
		switch (option)
		{
		case (uint16_t)Commond::_DirectionalLightAmbient:exe<1>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_DirectionalLightDiffuse:exe<2>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_DirectionalLightSpecular:exe<3>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_DirectionalLightDirection:exe<4>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_PointLightAmbient:exe<5>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_PointLightDiffuse:exe<6>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_PointLightSpecular:exe<7>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_PointLightConstant:exe<8>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_PointLightLinear:exe<9>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_PointLightQuadratic:exe<10>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_SpotLightAmbient:exe<11>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_SpotLightDiffuse:exe<12>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_SpotLightSpecular:exe<13>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_SpotLightCutOff:exe<14>(m_commands[i].m_data); break;
		default:
			break;
		}
	}
}

template<>
void LightSystem::exe<1>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<DirectionalLightComponent>();
			if (component)
				component->setAmbient(Vector3(value[0], value[1], value[2]));
		}
	}
}
template<>
void LightSystem::exe<2>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<DirectionalLightComponent>();
			if (component)
				component->setDiffuse(Vector3(value[0], value[1], value[2]));
		}
	}
}
template<>
void LightSystem::exe<3>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<DirectionalLightComponent>();
			if (component)
				component->setSpecular(Vector3(value[0], value[1], value[2]));
		}
	}
}

template<>
void LightSystem::exe<4>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<DirectionalLightComponent>();
			if (component)
				component->setDirection(Vector3(value[0], value[1], value[2]));
		}
	}
}


template<>
void LightSystem::exe<5>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<PointLightComponent>();
			if (component)
				component->setAmbient(Vector3(value[0], value[1], value[2]));
		}
	}
}
template<>
void LightSystem::exe<6>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<PointLightComponent>();
			if (component)
				component->setDiffuse(Vector3(value[0], value[1], value[2]));
		}
	}
}
template<>
void LightSystem::exe<7>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<PointLightComponent>();
			if (component)
				component->setSpecular(Vector3(value[0], value[1], value[2]));
		}
	}
}

template<>
void LightSystem::exe<8>(std::string exeCommand)
{
	int64_t id = 0;
	float value;
	if (getFloatValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<PointLightComponent>();
			if (component)
				component->setConstant(value);
		}
	}
}

template<>
void LightSystem::exe<9>(std::string exeCommand)
{
	int64_t id = 0;
	float value;
	if (getFloatValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<PointLightComponent>();
			if (component)
				component->setLinear(value);
		}
	}
}

template<>
void LightSystem::exe<10>(std::string exeCommand)
{
	int64_t id = 0;
	float value;
	if (getFloatValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<PointLightComponent>();
			if (component)
				component->setQuadratic(value);
		}
	}
}


template<>
void LightSystem::exe<11>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<SpotLightComponent>();
			if (component)
				component->setAmbient(Vector3(value[0], value[1], value[2]));
		}
	}
}
template<>
void LightSystem::exe<12>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<SpotLightComponent>();
			if (component)
				component->setDiffuse(Vector3(value[0], value[1], value[2]));
		}
	}
}
template<>
void LightSystem::exe<13>(std::string exeCommand)
{
	int64_t id = 0;
	std::vector<float> value;
	if (getV3Value(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<SpotLightComponent>();
			if (component)
				component->setSpecular(Vector3(value[0], value[1], value[2]));
		}
	}
}

template<>
void LightSystem::exe<14>(std::string exeCommand)
{
	int64_t id = 0;
	float value;
	if (getFloatValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<SpotLightComponent>();
			if (component)
				component->setCutOff(value);
		}
	}
}