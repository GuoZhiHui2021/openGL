#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <scene/instance.h>
#include <common/coordinateType.h>
class RenderData;
struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords[8];
};
class MeshNodeInstance :public Instance
{
public:
	virtual void getRenderDatas(std::vector<RenderData*>& datas,std::string material) = 0;
	virtual void setMaterial(std::string material) {}
	virtual std::string getMaterial()
	{
		return "";
	}
};
class Mesh:public MeshNodeInstance
{
public:
	virtual void getRenderDatas(std::vector<RenderData*> &datas, std::string material) override;
	void load(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::unordered_map<std::string, std::string> &textures,std::string material,int numTexCoord);
	virtual std::string getInstanceType()
	{
		return "Mesh";
	}
	virtual void setMaterial(std::string material) override;
	virtual std::string getMaterial()
	{
		return m_material;
	}
	~Mesh();
private:
	void ready();
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::unordered_map<std::string, std::string> m_textures;
	std::string m_material;
	int m_numTexCoord = 0;
	unsigned int m_VBO = 0;
	unsigned int m_VAO = 0;
	unsigned int m_EBO = 0;
	bool m_isReady = false;
	bool m_isloaded = false;
};

class Model:public MeshNodeInstance
{
public:
	virtual void getRenderDatas(std::vector<RenderData*>& datas, std::string material) override;
	void add(MeshNodeInstance* node);
	virtual std::string getInstanceType()
	{
		return "Model";
	}
private:
	std::vector<MeshNodeInstance*> m_nodes;
};

