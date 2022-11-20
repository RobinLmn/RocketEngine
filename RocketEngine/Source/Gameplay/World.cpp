#include <Gameplay/World.h>
#include <Gameplay/Scene.h>

#include <Gameplay/Systems/MeshLoadingSystem.h>
#include <Gameplay/Systems/CameraControlSystem.h>

namespace RocketEngine
{
    World::World()
        : registry{}
        , scene{}
        , systems{nullptr}
    {
        systems =
        {
            new CameraControlSystem(&registry),
            new MeshLoadingSystem(&registry)
        };
    }

    auto World::begin() -> void
    {
        scene.instantiate(&registry);

        for (auto system: systems)
        {
            if (system == nullptr) continue;
            system->begin();
        }
    }

    auto World::update(double dt) -> void
    {
        for (auto system: systems)
        {
            if (system == nullptr) continue;
            system->update(dt);
        }
    }

    World::~World()
    {
        for (auto system : systems) delete system;
    }
}
