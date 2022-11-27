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
        World(Window* window);
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
        decltype(auto) inline addComponents(entt::registry::entity_type entity)
        {
            return registry.emplace<T_Component...>(entity);
        }

        auto inline isKeyPressed(int key) -> bool { return window->isKeyPressed(key); }
        auto inline getAspectRatio() -> bool { return window->getAspectRatio(); }
            
    private:
        template<typename T_System>
        auto addSystem() -> void;
        
    private:
        entt::registry registry;
        Scene scene;
        std::vector<System*> systems;

        // hacky! fix
        Window* window;
    };
}
