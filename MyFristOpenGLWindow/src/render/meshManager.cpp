#include "meshManager.h"
#include "mesh.h"
#include "meshTool.h"

MeshNodeInstance* MeshManager::getOrCreateMesh(std::string meshName)
{
    if (m_meshes.find(meshName) != m_meshes.end())
    {
        return m_meshes[meshName];
    }
    if (meshName == "Box")
    {
        Mesh* mesh = new Mesh();

        const Vector3 boxPosition[8] = { Vector3(-0.5f,-0.5f,-0.5f),Vector3(0.5f,-0.5f,-0.5f),Vector3(-0.5f,0.5f,-0.5f),Vector3(0.5f,0.5f,-0.5f),Vector3(-0.5f,-0.5f,0.5f),Vector3(0.5f,-0.5f,0.5f),Vector3(-0.5f,0.5f,0.5f),Vector3(0.5f,0.5f,0.5f) };
        const uint8_t boxIndices[36] = { 1,0,3,0,2,3,3,2,7,2,6,7,4,5,6,5,7,6,4,5,0,5,1,0,0,4,2,4,6,2,5,1,7,1,3,7 };
        const float boxNormal[18] = { 0.0f,0.0f,-1.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,-1.0f,0.0f,-1.0f,0.0f,0.0f,1.0f,0.0f,0.0f };
        const float boxTexCoord[12] = { 0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f };

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
        std::unordered_map<std::string, std::string> textures;
        for (size_t i = 0; i < sizeof(boxIndices); i++)
        {
            Vector3 p = boxPosition[boxIndices[i]];
            size_t u = i % 6 * 2;
            size_t v = u + 1;
            size_t normal = i / 6 * 3;
            vertices.emplace_back();
            vertices.back().position = Vector3(p.getVec3().x, p.getVec3().y, p.getVec3().z);
            vertices.back().normal = Vector3(boxNormal[normal], boxNormal[normal + 1], boxNormal[normal + 2]);
            vertices.back().texCoords[0] = Vector2(boxTexCoord[u], boxTexCoord[v]);
        }

        mesh->load(vertices, indices, textures, "material/phong.materialPrototype",1);
        m_meshes.insert(std::make_pair(meshName, mesh));
        return mesh;
    }
    else
    {
        MeshNodeInstance* mesh = MeshTool::Instance()->import(meshName);
        if(mesh)
            m_meshes.insert(std::make_pair(meshName, mesh));
        return mesh;
    }
    
    return nullptr;
}
