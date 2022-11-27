#include <Gameplay/Systems/CameraControlSystem.h>

#include <Gameplay/Components/Camera.h>
#include <Gameplay/Components/Transform.h>

#include <Core/World.h>

#include <glfw/glfw3.h>

namespace RocketEngine
{
    CameraControlSystem::CameraControlSystem(World* world)
        : System(world)
    {
    }

    auto CameraControlSystem::update(double dt) -> void
    {
        for (auto [entity, camera, transform] : world->getEntities<Camera, Transform>())
        {
            camera.aspect = world->getAspectRatio();

            if (world->isKeyPressed(GLFW_KEY_D)) transform.position.x -= camera.speed * dt;
            if (world->isKeyPressed(GLFW_KEY_A)) transform.position.x += camera.speed * dt;
            if (world->isKeyPressed(GLFW_KEY_W)) transform.position.z += camera.speed * dt * 20.f;
            if (world->isKeyPressed(GLFW_KEY_S)) transform.position.z -= camera.speed * dt * 20.f;
            if (world->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) transform.position.y += camera.speed * dt;
            if (world->isKeyPressed(GLFW_KEY_SPACE)) transform.position.y -= camera.speed * dt;

            world->getOrAddComponents<TransformDirtyTag>(entity);
            world->getOrAddComponents<CameraDirtyTag>(entity);
        }
    }
}
