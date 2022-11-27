#pragma once
#include <Core/System.h>

namespace RocketEngine
{
    class CameraControlSystem final : public System
    {
    public:
        CameraControlSystem(World*);
        
    public:
        virtual auto update(double dt) -> void override;
    };
}
