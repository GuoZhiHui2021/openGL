#pragma once
#include "instance.h"
#include <common/singleton.h>
#include <system/system.h>
#include <vector>
class World :public Singleton<World>
{
public:
    World();
    ~World();
    void setFrameRate(uint16_t frameRate);
    long long getTickInterval()
    {
        return m_tickInterval;
    }
    long long getWorldTime()
    {
        return m_worldTime_millitm;
    }
    void tick();
private:
    uint16_t m_frameRate = 60;
    long long m_timeInterval = 1.0 / 60 * 1000;
    uint16_t m_last_frameRate = 0;
    uint16_t m_cur_frameRate = 0;
    long long m_tickInterval = 0;
    long long last_second_millitm = 0;
    long long last_frame_millitm = 0;
    long long m_worldTime_millitm = 0;

    std::vector<System*> m_systems;
};

