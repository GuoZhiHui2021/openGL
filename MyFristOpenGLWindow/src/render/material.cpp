
#include "material.h"
#include "materialManager.h"

MaterialPrototype::MaterialPrototype(std::string src)
{
	m_name = src;
}

MaterialPrototype::~MaterialPrototype()
{
	for (auto attr : m_attrs)
	{
		if (attr.second.m_value)
			free(attr.second.m_value);
		attr.second.m_value = NULL;
	}
}

void MaterialPrototype::insertMaterialPrototypeAttr(std::string name,uint16_t type, std::string serializedValue)
{
	if (void* value = MaterialManager::Instance()->deserialization(type, serializedValue))
	{
		insertMaterialPrototypeAttr(name, type, value);
	}
}

void MaterialPrototype::insertMaterialPrototypeAttr(std::string name, uint16_t type, void* value)
{
	if (m_attrs.find(name) == m_attrs.end())
	{
		MaterialPrototypeAttr attr;
		attr.m_name = name;
		attr.m_type = type;
		attr.m_value = value;
		m_attrs.insert(std::make_pair(name, attr));
	}
	else
	{
		MaterialPrototypeAttr attr = m_attrs[name];
		free(attr.m_value);
		attr.m_type = type;
		attr.m_value = value;
	}
}

void MaterialPrototype::insertMaterialPrototypeShader(std::string name, uint16_t type, std::string serializedValue)
{
	if (void* value = MaterialManager::Instance()->deserialization(type, serializedValue))
	{
		insertMaterialPrototypeShader(name, type, value);
	}
}

void MaterialPrototype::insertMaterialPrototypeShader(std::string name, uint16_t type, void* value)
{
	if (m_shaders.find(type) == m_shaders.end())
	{
		MaterialPrototypeAttr attr;
		attr.m_name = name;
		attr.m_type = type;
		attr.m_value = value;
		m_shaders.insert(std::make_pair(type, attr));
	}
	else
	{
		MaterialPrototypeAttr attr = m_shaders[type];
		free(attr.m_value);
		attr.m_name = name;
		attr.m_value = value;
	}
}

std::vector<MaterialPrototypeAttr> MaterialPrototype::getAttrs() const
{
	std::vector<MaterialPrototypeAttr> ret;
	for (auto attr : m_attrs)
	{
		ret.push_back(attr.second.clone());
	}
	return ret;
}

std::vector<MaterialPrototypeAttr> MaterialPrototype::getShaders() const
{
	std::vector<MaterialPrototypeAttr> ret;
	for (auto attr : m_shaders)
	{	
		ret.push_back(attr.second.clone());
	}
	return ret;
}

MaterialPrototypeAttr MaterialPrototype::getAttr(std::string attrName) const
{
	auto iter = m_attrs.find(attrName);
	if (iter != m_attrs.end())
	{
		return iter->second.clone();
	}
	return MaterialPrototypeAttr();
}

uint16_t MaterialPrototype::getAttrType(std::string attrName) const
{
	auto iter = m_attrs.find(attrName);
	if (iter != m_attrs.end())
	{
		return iter->second.m_type;
	}
	return 0;
}

void MaterialPrototype::setRenderType(std::string type)
{
	m_renderType = type;
}

std::string MaterialPrototype::getRenderType() const
{
	return m_renderType;
}

Material::Material(std::string src,const MaterialPrototype& prototype)
{
	m_name = src;
	m_prototype = prototype.getName();
}

Material::~Material()
{
	for (auto attr : m_attrs)
	{
		if (attr.second.m_value)
			free(attr.second.m_value);
		attr.second.m_value = NULL;
	}
}

bool Material::setAttribute(std::string name, void* value)
{
	if (!value)
		return false;
	if (m_attrs.find(name) != m_attrs.end())
	{
		void* old_value = m_attrs[name].m_value;
		m_attrs[name].m_value = value;
		free(old_value);
	}
	else
	{
		MaterialPrototype* prototype = MaterialManager::Instance()->getOrCreateMaterialPrototype(m_prototype);
		if (!prototype)
			return false;
		if (prototype->getAttr(name).isEmpty())
			return false;
		MaterialAttr attr;
		attr.m_name = name;
		attr.m_value = value;
		m_attrs[name] = attr;
	}
}

std::vector<MaterialPrototypeAttr> Material::getAttrs() const
{
	if(m_prototype.empty()||!MaterialManager::Instance()->getOrCreateMaterialPrototype(m_prototype))
		return std::vector<MaterialPrototypeAttr>();
	std::vector<MaterialPrototypeAttr> attrs = MaterialManager::Instance()->getOrCreateMaterialPrototype(m_prototype)->getAttrs();
	for (size_t i = 0; i < attrs.size(); i++)
	{
		auto iter = m_attrs.find(attrs[i].m_name);
		if (iter != m_attrs.end())
		{
			size_t size = MaterialManager::Instance()->getDataSize(attrs[i].m_type);
			memcpy_s(attrs[i].m_value, size, iter->second.m_value,size);
		}
	}
	return attrs;
}

MaterialPrototypeAttr Material::getAttr(std::string attrName) const
{
	MaterialPrototype* prototype = MaterialManager::Instance()->getOrCreateMaterialPrototype(m_prototype);
	if(!prototype)
		return MaterialPrototypeAttr();
	auto attr = prototype->getAttr(attrName);
	if(attr.isEmpty())
		return MaterialPrototypeAttr();
	auto m_attr = m_attrs.find(attrName);
	if (m_attr != m_attrs.end())
	{
		size_t size = MaterialManager::Instance()->getDataSize(attr.m_type);
		if (attr.m_value)
			free(attr.m_value);
		attr.m_value = malloc(size);
		memcpy_s(attr.m_value, size, m_attr->second.m_value, size);
	}
	return attr;
}

MaterialPrototypeAttr MaterialPrototypeAttr::clone() const
{
	MaterialPrototypeAttr attr;
	if (!isEmpty())
	{
		attr.m_name = m_name;
		attr.m_type = m_type;
		size_t size = MaterialManager::Instance()->isShaderType(m_type)? strlen((char*)m_value)+1: MaterialManager::Instance()->getDataSize(m_type);
		attr.m_value = malloc(size);
		memcpy_s(attr.m_value, size, m_value, size);
	}
	return attr;
}
