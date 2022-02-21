#pragma once
#include <common/singleton.h>
class MeshNodeInstance;
struct aiNode;
struct aiMesh;
struct aiScene;
class MeshTool:public Singleton<MeshTool>
{
public:
	MeshNodeInstance* import(std::string path);
private:
	MeshNodeInstance* processNode(aiNode* node,const aiScene* scene,std::string directory);
	MeshNodeInstance* processMesh(aiMesh* node, const aiScene* scene, std::string directory);
};

