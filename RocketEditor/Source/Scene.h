#pragma once

#include <Gameplay/Scene.h>

namespace RocketGame
{
    class RocketEngine::World;

    class Scene final : public RocketEngine::Scene
    {
    public:
        virtual auto instantiate(RocketEngine::World* world) -> void override;
    };
}
