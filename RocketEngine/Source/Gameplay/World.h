#pragma once
#include <Core/System.h>
#include <Gameplay/Scene.h>
#include <entt/entity/registry.hpp>

namespace RocketEngine
{
    class World final
    {
    public:
        World();
        ~World();
        
    public:
        auto begin() -> void;
        auto update(double dt) -> void;
        
        [[nodiscard]]
        auto getRegistry() -> entt::registry* { return &registry; };
        
    private:
        entt::registry registry;
        Scene scene;
        std::array<System*, 8> systems;
    };
}
