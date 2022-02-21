#pragma once
#include <common/singleton.h>
#include <string>
#include <unordered_map>
#include "meshTool.h"
#include "mesh.h"
class MeshManager:public Singleton<MeshManager>
{
public:
	MeshNodeInstance* getOrCreateMesh(std::string meshName);
private:
	std::unordered_map<std::string, class MeshNodeInstance*> m_meshes;
};

