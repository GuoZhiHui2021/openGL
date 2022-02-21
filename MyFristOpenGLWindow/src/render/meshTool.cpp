#include "meshTool.h"
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "textureManager.h"

std::unordered_map<std::string, std::string> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName,std::string directory)
{
    std::unordered_map<std::string, std::string> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string texturePath = directory + "/" + std::string(str.C_Str());
        Texture* texture = TextureManager::Instance()->getOrCreateTexture(texturePath);
        if (texture)
        {
            textures.insert(std::make_pair(typeName + "[" +  std::to_string(i) + "]", texturePath));
        }
        else
        {
            textures.insert(std::make_pair(typeName + "[" + std::to_string(i) + "]", "0XFFFFFFFF"));
        }
    }
    return textures;
}

MeshNodeInstance* MeshTool::import(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return nullptr;
    }
    std::string directory = path.substr(0, path.find_last_of('/'));
    return processNode(scene->mRootNode, scene, directory);
}

MeshNodeInstance* MeshTool::processNode(aiNode* node,const aiScene* scene,std::string directory)
{
    Model *model = new Model();
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        model->add(processMesh(mesh, scene, directory));
    }
    // 接下来对它的子节点重复这一过程
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        model->add(processNode(node->mChildren[i], scene, directory));
    }
    return model;
}

MeshNodeInstance* MeshTool::processMesh(aiMesh* node, const aiScene* scene,std::string directory)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::unordered_map<std::string, std::string> textures;
    int numTexCoord = 1;
    for (unsigned int i = 0; i < node->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.position = Vector3(node->mVertices[i].x, node->mVertices[i].y, node->mVertices[i].z);
        vertex.normal = Vector3(node->mNormals[i].x, node->mNormals[i].y, node->mNormals[i].z);
        for (int j = 0; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; j++)
        {
            if (!node->mTextureCoords[j])
                break;
            vertex.texCoords[j] = Vector2(node->mTextureCoords[j][i].x, node->mTextureCoords[j][i].y);
            numTexCoord = std::max(j + 1, numTexCoord);
        }       
        vertices.push_back(vertex);
    }
    for (int i = 0; i < node->mNumFaces; i++)
    {
        aiFace face = node->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    std::string materialFile = "material/phong.materialPrototype";
    if (node->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[node->mMaterialIndex];
        int shadingModel = 0;
        material->Get(AI_MATKEY_SHADING_MODEL, shadingModel);

        /*switch (shadingModel)
        {
        default:
            break;
        case aiShadingMode_Phong:
        case aiShadingMode_Blinn:
        }*/
        
        std::unordered_map<std::string, std::string> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse", directory);
        std::unordered_map<std::string, std::string> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular", directory);
        for (auto diffuse : diffuseMaps)
        {
            if (textures.find(diffuse.first) == textures.end())
            {
                textures.insert(std::make_pair(diffuse.first, diffuse.second));
            }
        }
        for (auto specular : specularMaps)
        {
            if (textures.find(specular.first) == textures.end())
            {
                textures.insert(std::make_pair(specular.first, specular.second));
            }
        }
    }
    Mesh* mesh = new Mesh();
    mesh->load(vertices, indices, textures, materialFile, numTexCoord);
    return mesh;
}
