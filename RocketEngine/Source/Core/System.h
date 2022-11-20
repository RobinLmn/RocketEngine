#pragma once
#include <entt/entity/registry.hpp>

namespace RocketEngine
{
    class System
    {
    public:
        System(entt::registry* registry);
        
    public:
        virtual auto begin() -> void;
        virtual auto update(double dt) -> void;
        
    protected:
        entt::registry* registry;
    };
}
