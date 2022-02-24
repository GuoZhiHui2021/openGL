#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include <vector>
struct MaterialPrototypeAttr
{
	std::string m_name = "";
	uint16_t m_type = 0;
	void* m_value = NULL;
	MaterialPrototypeAttr clone() const;
	bool isEmpty() const
	{
		return m_name == "" || m_type == 0 || !m_value;
	}
};


class MaterialPrototype
{
public:
	MaterialPrototype(std::string src);
	~MaterialPrototype();
	void insertMaterialPrototypeAttr(std::string name, uint16_t type, std::string serializedValue);
	void insertMaterialPrototypeAttr(std::string name, uint16_t type, void* value);
	void insertMaterialPrototypeShader(std::string name, uint16_t type, std::string serializedValue);
	void insertMaterialPrototypeShader(std::string name, uint16_t type, void* value);
	std::string getName() const { return m_name; }
	std::vector<MaterialPrototypeAttr> getAttrs() const;
	std::vector<MaterialPrototypeAttr> getShaders() const;
	MaterialPrototypeAttr getAttr(std::string attrName) const;
	uint16_t getAttrType(std::string attrName) const;
	void setRenderType(std::string type);
	std::string getRenderType() const;
private:
	MaterialPrototype();
private:
	std::string m_name;
	std::string m_renderType;
	std::unordered_map<std::string, MaterialPrototypeAttr> m_attrs;
	std::unordered_map<uint16_t, MaterialPrototypeAttr> m_shaders;

};


struct MaterialAttr
{
	std::string m_name = "";
	void* m_value = NULL;
	bool isEmpty()
	{
		return m_name == "" || !m_value;
	}
};


class Material
{
public:
	Material(std::string src, const MaterialPrototype& prototype);
	~Material();

	bool setAttribute(std::string name, void* value);
	std::vector<MaterialPrototypeAttr> getAttrs() const;
	MaterialPrototypeAttr getAttr(std::string attrName) const;
	std::string getPrototype()
	{
		return m_prototype;
	}
private:
	Material();
private:
	std::string m_name;
	std::string m_prototype;
	std::unordered_map<std::string, MaterialAttr> m_attrs;
};

