#include <Core/World.h>
#include <Gameplay/Scene.h>

#include <Gameplay/Systems/MeshLoadingSystem.h>
#include <Gameplay/Systems/CameraControlSystem.h>

namespace RocketEngine
{
    World::World()
        : registry{}
        , scene{}
        , systems{}
    {
        addSystem<CameraControlSystem>();
        addSystem<MeshLoadingSystem>();
    }

    auto World::begin() -> void
    {
        scene.instantiate(&registry);

        for (auto& system: systems)
        {
            system->begin();
        }
    }

    auto World::update(double dt) -> void
    {
        for (auto& system: systems)
        {
            system->update(dt);
        }
    }

    auto World::end() -> void
    {
        for (auto& system : systems)
        {
            system->end();
        }
    }

    World::~World()
    {
        for (auto& system : systems)
        {
            delete system;
        }
    }

    template<typename T_System>
    auto World::addSystem() -> void
    {
        systems.push_back(new T_System{ this });
    }
}
