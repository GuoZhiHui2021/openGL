#pragma once
#include "system.h"

#define MAX_CUTOFF  45.0f
#define MIN_CUTOFF  12.0f
#define MAX_OUT_CUTOFF  60.0f
#define MIN_OUT_CUTOFF  15.0f

class LightSystem :
    public System
{
private:
    enum class Commond
    {
        _DirectionalLightAmbient = 1,
        _DirectionalLightDiffuse,
        _DirectionalLightSpecular,
        _DirectionalLightDirection,
        

        _PointLightAmbient,
        _PointLightDiffuse,
        _PointLightSpecular,
        _PointLightConstant,
        _PointLightLinear,
        _PointLightQuadratic,
       

        _SpotLightAmbient,
        _SpotLightDiffuse,
        _SpotLightSpecular,
        _SpotLightCutOff,
        _SpotLightOutCutOff,

        _DirectionalLightStrength,
        _PointLightStrength,
        _SpotLightStrength
    };
public:
    virtual int getOrder()
    {
        return 5500;
    }
    virtual uint16_t getSystemType()
    {
        return 10;
    }
protected:
    virtual void execute_implement();
private:
    template<uint16_t option>
    void exe(std::string exeCommand) {}

    template<>
    void exe<1>(std::string exeCommand);
    template<>
    void exe<2>(std::string exeCommand);
    template<>
    void exe<3>(std::string exeCommand);
    template<>
    void exe<4>(std::string exeCommand);
    template<>
    void exe<5>(std::string exeCommand);
    template<>
    void exe<6>(std::string exeCommand);
    template<>
    void exe<7>(std::string exeCommand);
    template<>
    void exe<8>(std::string exeCommand);
    template<>
    void exe<9>(std::string exeCommand);
    template<>
    void exe<10>(std::string exeCommand);
    template<>
    void exe<11>(std::string exeCommand);
    template<>
    void exe<12>(std::string exeCommand);
    template<>
    void exe<13>(std::string exeCommand);
    template<>
    void exe<14>(std::string exeCommand);
    template<>
    void exe<15>(std::string exeCommand);
    template<>
    void exe<16>(std::string exeCommand);
    template<>
    void exe<17>(std::string exeCommand);
    template<>
    void exe<18>(std::string exeCommand);
};

