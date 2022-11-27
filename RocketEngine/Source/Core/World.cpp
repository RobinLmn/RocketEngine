#include <Core/World.h>
#include <Gameplay/Scene.h>

#include <Gameplay/Systems/MeshLoadingSystem.h>
#include <Gameplay/Systems/CameraControlSystem.h>

namespace RocketEngine
{
    World::World(Window* window)
        : registry{}
        , scenes{}
        , systems{}
        , window{window}
    {
        addSystem<CameraControlSystem>();
        addSystem<MeshLoadingSystem>();
    }

    auto World::begin() -> void
    {
        for (auto& scene : scenes)
        {
            scene->instantiate(this);
        }

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

        for (auto& scene : scenes)
        {
            delete scene;
        }
    }

    template<typename T_System>
    auto World::addSystem() -> void
    {
        systems.push_back(new T_System{ this });
    }
}
