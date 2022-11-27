#include "Scene.h"

#include <Core/World.h>
#include <Systems/Editor.h>

namespace RocketEditor
{
    auto Scene::instantiate(RocketEngine::World* world) -> void
    {
        world->pushSystem<Editor>();
    }
}