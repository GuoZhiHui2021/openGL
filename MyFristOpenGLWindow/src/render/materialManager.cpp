#include "materialManager.h"
#include <common/fileUtil.h>
#include <common/util.h>
#include <render/textureManager.h>

#define MATERTAL_PROTO_TYPE  "materialPrototype"
#define MATERTAL "material"
#define PROTO_TYPE "prototype"
MaterialManager::MaterialManager() :m_materialPrototypes(), m_materials(), m_shaderTypeMap(), m_AttrTypeMap()
{
    m_shaderTypeMap.insert(std::make_pair("VERTEX_SHADER", GL_VERTEX_SHADER));
    m_shaderTypeMap.insert(std::make_pair("FRAGMENT_SHADER", GL_FRAGMENT_SHADER));

    m_AttrTypeMap.insert(std::make_pair("TEXTURE0", GL_TEXTURE0));
    m_AttrTypeMap.insert(std::make_pair("TEXTURE1", GL_TEXTURE1));
    m_AttrTypeMap.insert(std::make_pair("TEXTURE2", GL_TEXTURE2));
    m_AttrTypeMap.insert(std::make_pair("TEXTURE3", GL_TEXTURE3));
    m_AttrTypeMap.insert(std::make_pair("TEXTURE4", GL_TEXTURE4));
    m_AttrTypeMap.insert(std::make_pair("TEXTURE5", GL_TEXTURE5));
    m_AttrTypeMap.insert(std::make_pair("TEXTURE6", GL_TEXTURE6));
    m_AttrTypeMap.insert(std::make_pair("TEXTURE7", GL_TEXTURE7));

    m_AttrTypeMap.insert(std::make_pair("INT", GL_INT));
    m_AttrTypeMap.insert(std::make_pair("FLOAT", GL_FLOAT));
    m_AttrTypeMap.insert(std::make_pair("VEC2F", GL_FLOAT_VEC2));
    m_AttrTypeMap.insert(std::make_pair("VEC3F", GL_FLOAT_VEC3));
    m_AttrTypeMap.insert(std::make_pair("VEC4F", GL_FLOAT_VEC4));
}

MaterialPrototype* MaterialManager::getOrCreateMaterialPrototype(std::string name)
{
    if (m_materialPrototypes.find(name) != m_materialPrototypes.end())
        return m_materialPrototypes[name];
    std::vector<std::string> lines = readLines(name);
    bool vs = false,fs = false;
    bool legal = true;
    MaterialPrototype* prototype = new MaterialPrototype(name);
    for (auto line : lines)
    {
        std::string t_line = line;
        removeHTSpaces(t_line);
        if (t_line.empty())
        {
            continue;
        }
        std::vector<std::string> k_v = splitStr(line, ":");
        if (k_v.size() != 2)
            return nullptr;
        if (k_v[0] == "renderType")
        {
            prototype->setRenderType(k_v[1]);
            continue;
        }
        std::vector<std::string> paras = splitLevelStr(k_v[1].substr(1, k_v[1].length() - 2),",");
        if (paras.size() != 2)
            return nullptr;
        if (m_shaderTypeMap.find(paras[0]) != m_shaderTypeMap.end())
        {
            if (m_shaderTypeMap[paras[0]] == GL_VERTEX_SHADER)
                vs = true;
            else if (m_shaderTypeMap[paras[0]] == GL_FRAGMENT_SHADER)
                fs = true;
            prototype->insertMaterialPrototypeShader(k_v[0], m_shaderTypeMap[paras[0]], paras[1]);
        }
        else if (m_AttrTypeMap.find(paras[0]) != m_AttrTypeMap.end())
        {
            prototype->insertMaterialPrototypeAttr(k_v[0], m_AttrTypeMap[paras[0]], paras[1]);
        }
        else
        {
            legal = false;
            break;
        }
    }
    if(!vs||!fs)
        legal = false;
    if (!legal)
    {
        delete prototype;
        prototype = nullptr;
    }   
    else
    {
        m_materialPrototypes[name] = prototype;
    }
    return prototype;
}

Material* MaterialManager::getOrCreateMaterial(std::string name)
{
    if (m_materials.find(name) != m_materials.end())
        return m_materials[name];
    std::vector<std::string> name_suffix = splitStr(name, ".");
    if (name_suffix.size() != 2)
        return nullptr;
    if (name_suffix[1] == MATERTAL_PROTO_TYPE)
    {
        std::string materialName = name_suffix[0].append("Default.").append(MATERTAL);
        MaterialPrototype* protoType = getOrCreateMaterialPrototype(name);
        if (!protoType)
            return nullptr;
        if (m_materials.find(materialName) != m_materials.end())
            return m_materials[materialName];
        Material* material = new Material(materialName, *protoType);
        m_materials[materialName] = material;
        return material;
    }
    else if (name_suffix[1] == MATERTAL)
    {
        std::string materialName = name;
        std::vector<std::string> lines = readLines(name);
        if (lines.size() < 1)
            return nullptr;
        std::vector<std::string> prototypeStrs = splitStr(lines[0], ":");
        if (prototypeStrs.size() != 2 || prototypeStrs[0] != PROTO_TYPE || !getOrCreateMaterialPrototype(prototypeStrs[1]))
            return nullptr;
        MaterialPrototype* prototype = getOrCreateMaterialPrototype(prototypeStrs[1]);
        Material* material = new Material(name, *prototype);
        for (size_t i = 1;i<lines.size();i++)
        {
            std::string line = lines[i];
            std::string t_line = line;
            removeHTSpaces(t_line);
            if (t_line.empty())
            {
                continue;
            }
            std::vector<std::string> strs = splitStr(line, ":");
            if (strs.size() != 2)
                return nullptr;
            uint16_t type = prototype->getAttrType(strs[0]);
            std::vector<std::string> slstrs = splitLevelStr(strs[1].substr(1, strs[1].length() - 2), ",");
            if (slstrs.size() != 2)
                return nullptr;
            void* value = deserialization(type, slstrs[1]);
            if (!value or !material->setAttribute(strs[0], value))
            {
                if (value)
                    free(value);
                delete material;
                return nullptr;
            }   
        }
        m_materials[name] = material;
        return material;
    }
    
    
    return nullptr;
}

void* MaterialManager::deserialization(uint16_t type, std::string src)
{
    char* c;
    void* ret;
    char* b;
    std::vector<std::string> strs;
    switch (type)
    {
    case(GL_INT):return deserialization<GL_INT>(src);
    case(GL_FLOAT):return deserialization<GL_FLOAT>(src);
    case(GL_FLOAT_VEC2):return deserialization<GL_FLOAT_VEC2>(src);
    case(GL_FLOAT_VEC3):return deserialization<GL_FLOAT_VEC3>(src);
    case(GL_FLOAT_VEC4):return deserialization<GL_FLOAT_VEC4>(src);
    case(GL_VERTEX_SHADER):
    case(GL_FRAGMENT_SHADER):
        c = (char*)src.c_str();
        ret = malloc(strlen(c)+1);
        memcpy_s(ret, strlen(c)+1, c, strlen(c)+1);
        return ret;
    case(GL_TEXTURE0):
    case(GL_TEXTURE1):
    case(GL_TEXTURE2):
    case(GL_TEXTURE3):
    case(GL_TEXTURE4):
    case(GL_TEXTURE5):
    case(GL_TEXTURE6):
    case(GL_TEXTURE7):
        strs = splitLevelStr(src.substr(1, src.length() - 2), ",");
        if (strs.size() != 5)
            return nullptr;
        ret = malloc(sizeof(uint16_t) * 4 + 127);
        for (size_t i = 0; i < 4;i++)
        {
            uint16_t option = TextureManager::Instance()->getOption(strs[i + 1]);
            memcpy_s((char*)ret + sizeof(uint16_t) * i, sizeof(uint16_t), &option, sizeof(uint16_t));
        }
        c = (char*)strs[0].c_str();
        memcpy_s((char*)ret + sizeof(uint16_t) * 4, strlen(c)+1, c, strlen(c)+1);
        return ret;
    default:return nullptr;
    }
    return nullptr;
}

size_t MaterialManager::getDataSize(uint16_t type)
{
    switch (type)
    {
    case(GL_INT):return 4;
    case(GL_FLOAT):return 4;
    case(GL_FLOAT_VEC2):return 4 * 2;
    case(GL_FLOAT_VEC3):return 4 * 3;
    case(GL_FLOAT_VEC4):return 4 * 4;
    case(GL_TEXTURE0):
    case(GL_TEXTURE1):
    case(GL_TEXTURE2):
    case(GL_TEXTURE3):
    case(GL_TEXTURE4):
    case(GL_TEXTURE5):
    case(GL_TEXTURE6):
    case(GL_TEXTURE7):
        return sizeof(uint16_t) * 4 + 127;
    default:return 0;
    }
    return 0;
}

template<uint16_t T>
void* MaterialManager::deserialization(std::string src)
{
    return nullptr;
}

template<>
void* MaterialManager::deserialization<GL_INT>(std::string src)
{
    int i;
    if (strToInt(src.c_str(), i))
    {
        void* ret = malloc(sizeof(int));
        memcpy_s(ret, sizeof(int), &i, sizeof(int));
        return ret;
    }
    return nullptr;
}

template<>
void* MaterialManager::deserialization<GL_FLOAT>(std::string src)
{
    float f;
    if (strToFloat(src.c_str(), f))
    {
        void* ret = malloc(sizeof(float));
        memcpy_s(ret, sizeof(float), &f, sizeof(float));
        return ret;
    }
    return nullptr;
}

template<>
void* MaterialManager::deserialization<GL_FLOAT_VEC2>(std::string src)
{
    src = src.substr(1, src.length() - 2);
    std::vector<std::string> strs = splitLevelStr(src, ",");
    if (strs.size() != 2)
        return nullptr;
    float f[2];
    for (size_t i = 0; i < 2; i++)
    {
        if (!strToFloat(strs[i].c_str(), f[i]))
        {
            return nullptr;
        }
    }
    void* ret = malloc(sizeof(float) * 2);
    memcpy_s(ret, sizeof(float) * 2, f, sizeof(float) * 2);
    return ret;
}

template<>
void* MaterialManager::deserialization<GL_FLOAT_VEC3>(std::string src)
{
    src = src.substr(1, src.length() - 2);
    std::vector<std::string> strs = splitLevelStr(src, ",");
    if (strs.size() != 3)
        return nullptr;
    float f[3];
    for (size_t i = 0; i < 3; i++)
    {
        if (!strToFloat(strs[i].c_str(), f[i]))
        {
            return nullptr;
        }
    }
    void* ret = malloc(sizeof(float) * 3);
    memcpy_s(ret, sizeof(float) * 3, f, sizeof(float) * 3);
    return ret;
}

template<>
void* MaterialManager::deserialization<GL_FLOAT_VEC4>(std::string src)
{
    src = src.substr(1, src.length() - 2);
    std::vector<std::string> strs = splitLevelStr(src, ",");
    if (strs.size() != 4)
        return nullptr;
    float f[4];
    for (size_t i = 0; i < 4; i++)
    {
        if (!strToFloat(strs[i].c_str(), f[i]))
        {
            return nullptr;
        }
    }
    void* ret = malloc(sizeof(float) * 4);
    memcpy_s(ret, sizeof(float) * 4, f, sizeof(float) * 4);
    return ret;
}
