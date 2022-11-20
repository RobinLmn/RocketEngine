#include <Gameplay/Scene.h>

#include <Gameplay/Components/Camera.h>
#include <Gameplay/Components/Mesh.h>
#include <Gameplay/Components/Transform.h>
#include <Gameplay/Components/Light.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace
{
    using namespace RocketEngine;

    auto makeCamera(entt::registry* registry)
    {
        const auto cameraEntity = registry->create();
        
        auto& cameraTransform = registry->emplace<Transform>(cameraEntity);
        cameraTransform.position = {0.f, -0.06f, -12.f};
        cameraTransform.scale = {1.f, 1.f, 1.f};
        cameraTransform.rotation = {0.f, 0.f, 0.f};
        
        auto& cameraComponent = registry->emplace<Camera>(cameraEntity);
        cameraComponent.isMainCamera = true;
        cameraComponent.near = 0.03f;
        cameraComponent.far = 100.f;
        cameraComponent.aspect = 1.f;
        cameraComponent.fov = glm::radians(45.f);
        cameraComponent.speed = 0.1f;
        cameraComponent.sensitivity = 1.f;
    }

    auto makeObj(entt::registry* registry, const char* obj)
    {
        const auto entity = registry->create();
        
        auto& entityMesh = registry->emplace<MeshPath>(entity);
        entityMesh.path = obj;
        
        auto& entityTransform = registry->emplace<Transform>(entity);
        entityTransform.position = {0.f, 0.f, 0.f};
        entityTransform.scale = {1.f, 1.f, 1.f};
        entityTransform.rotation = {0.f, 0.f, 0.f};
    }

    auto makeLight(entt::registry* registry)
    {
        const auto lightEntity = registry->create();
        
        auto& lightComponent = registry->emplace<Light>(lightEntity);
        lightComponent.color = {1.f, 1.f, 1.f};
        lightComponent.ambientStrength = 0.1f;
        lightComponent.diffuseStrength = 2.f;
        
        auto& lightTransform = registry->emplace<Transform>(lightEntity);
        lightTransform.position = {10.f, 10.f, 0.f};
    }
}

namespace RocketEngine
{
    auto Scene::instantiate(entt::registry* registry) -> void
    {
        const auto triangle = registry->create();
    }
}
