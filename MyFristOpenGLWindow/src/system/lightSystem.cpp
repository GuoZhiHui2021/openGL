#include "lightSystem.h"
#include <common/fileUtil.h>
#include <common/util.h>

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
		case (uint16_t)Commond::_SpotLightOutCutOff:exe<15>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_DirectionalLightStrength:exe<16>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_PointLightStrength:exe<17>(m_commands[i].m_data); break;
		case (uint16_t)Commond::_SpotLightStrength:exe<18>(m_commands[i].m_data); break;
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
				component->setCutOff(std::clamp(value, MIN_CUTOFF, MAX_CUTOFF));
		}
	}
}

template<>
void LightSystem::exe<15>(std::string exeCommand)
{
	int64_t id = 0;
	float value;
	if (getFloatValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<SpotLightComponent>();
			if (component)
				component->setOutCutOff(std::clamp(value,MIN_OUT_CUTOFF,MAX_OUT_CUTOFF));
		}
	}
}

template<>
void LightSystem::exe<16>(std::string exeCommand)
{
	int64_t id = 0;
	float value;
	if (getFloatValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<DirectionalLightComponent>();
			if (component)
				component->setStrength(max(value, 0.0f));
		}
	}
}

template<>
void LightSystem::exe<17>(std::string exeCommand)
{
	int64_t id = 0;
	float value;
	if (getFloatValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<PointLightComponent>();
			if (component)
				component->setStrength(max(value, 0.0f));
		}
	}
}

template<>
void LightSystem::exe<18>(std::string exeCommand)
{
	int64_t id = 0;
	float value;
	if (getFloatValue(exeCommand, id, value))
	{
		if (auto entity = getEntity(id))
		{
			auto component = entity->getComponent<SpotLightComponent>();
			if (component)
				component->setStrength(max(value, 0.0f));
		}
	}
}