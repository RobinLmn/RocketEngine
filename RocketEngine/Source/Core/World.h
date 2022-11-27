#pragma once

#include <Core/System.h>
#include <Gameplay/Scene.h>
#include <entt/entity/registry.hpp>
#include <vector>
#include <Core/Window.h>

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
        auto inline getOrAddComponents(entt::registry::entity_type entity) -> decltype(auto)
        {
            return registry.get_or_emplace<T_Component...>(entity);
        }

        template<typename... T_Component>
        auto inline removeComponents(entt::registry::entity_type entity) -> void
        {
            registry.remove<T_Component...>(entity);
        }

        auto inline spawnEntity() -> decltype(auto)
        {
            return registry.create();
        }
           
        template<typename T_Scene>
        auto pushScene() -> void
        {
            scenes.push_back(new T_Scene{});
        }

        template<typename T_System>
        auto pushSystem() -> void
        {
            systems.push_back(new T_System{ this });
        }

    private:
        entt::registry registry;
        std::vector<Scene*> scenes;
        std::vector<System*> systems;
    };
}
