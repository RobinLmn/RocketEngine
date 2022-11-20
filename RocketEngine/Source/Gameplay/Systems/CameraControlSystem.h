#pragma once
#include <Core/System.h>

namespace RocketEngine
{
    class CameraControlSystem final : public System
    {
    public:
        CameraControlSystem(entt::registry*);
        
    public:
        auto update(double dt) -> void override;
    };
}
