#pragma once
#include <entt/entity/registry.hpp>

namespace RocketEngine
{
    class Scene final
    {
    public:
        auto instantiate(entt::registry*) -> void;
    };
}
