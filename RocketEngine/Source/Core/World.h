#pragma once

#include <Core/System.h>
#include <Gameplay/Scene.h>
#include <entt/entity/registry.hpp>
#include <vector>

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
        auto end() -> void;

        template<typename... T_Component>
        [[nodiscard]] decltype(auto) inline getEntities()
        {
            return registry.view<T_Component...>().each();
        }

        template<typename... T_Component>
        [[nodiscard]] decltype(auto) inline addComponents(entt::registry::entity_type entity)
        {
            return registry.emplace<T_Component...>(entity);
        }
            
    private:
        template<typename T_System>
        auto addSystem() -> void;
        
    private:
        entt::registry registry;
        Scene scene;
        std::vector<System*> systems;
    };
}
