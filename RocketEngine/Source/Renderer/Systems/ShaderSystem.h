#pragma once
#include <Core/System.h>

namespace RocketEngine
{
    class World;

    class ShaderSystem final : public System
    {
    public:
        ShaderSystem(World* world);

    public:
        virtual auto begin() -> void override;
        virtual auto update(double dt) -> void override;
    };
}