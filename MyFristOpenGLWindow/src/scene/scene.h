#pragma once
#include <unordered_map>
#include <vector>
#include "entity.h"
class Scene :
    public Instance
{
public:
    virtual std::string getInstanceType()
    {
        return "Scene";
    }
    bool add(Entity* entity);
    bool addEntityDFS(Entity* entity);
    void remove(uint64_t entityId);
    void remove(Entity* entity);
    bool atScene(uint64_t entityId);
    Entity* getEntity(uint64_t entityId);
    void clear();
    std::vector<Entity*> separateSustainedEntities();
    std::vector<Entity*> getEntities();
    void setSceneId(int64_t id)
    {
        m_scene_id = id;
    }
    int64_t getSceneId()
    {
        return m_scene_id;
    }
protected:
    virtual void setParent_implement(Instance* instance);
private:
    void removeFromEntities(uint64_t entityId);
    void eraseEntity(Entity* entity);
private:
    std::unordered_map<uint64_t,Entity*> m_entities;
    int64_t m_scene_id;
};

