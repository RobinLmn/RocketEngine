#include <Gameplay/Scene.h>

#include <Gameplay/Components/Camera.h>
#include <Gameplay/Components/Mesh.h>
#include <Gameplay/Components/Material.h>
#include <Gameplay/Components/Transform.h>
#include <Gameplay/Components/Light.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace
{
    using namespace RocketEngine;

    auto makeCamera(entt::registry* registry) -> void
    {
        const auto cameraEntity = registry->create();
        
        auto& cameraTransform = registry->emplace<Transform>(cameraEntity);
        cameraTransform.position = {0.f, 0.f, -15.f};
        cameraTransform.scale = {1.f, 1.f, 1.f};
        cameraTransform.rotation = {0.f, 0.f, 0.f};
        
        auto& cameraComponent = registry->emplace<Camera>(cameraEntity);
        cameraComponent.isMainCamera = true;
        cameraComponent.near = 0.03f;
        cameraComponent.far = 100.f;
        cameraComponent.aspect = 1.f;
        cameraComponent.fov = glm::radians(45.f);
        cameraComponent.speed = 0.5f;
        cameraComponent.sensitivity = 1.f;
    }

    auto makeObj(entt::registry* registry, const char* obj) -> void
    {
        const auto entity = registry->create();
        
        auto& entityMesh = registry->emplace<Model>(entity);
        entityMesh.path = obj;
        
        auto& entityTransform = registry->emplace<Transform>(entity);
        entityTransform.position = {0.f, 0.f, 0.f};
        entityTransform.scale = {0.1f, 0.1f, 0.1f};
        entityTransform.rotation = {45.f, 45.f, 45.f};

        auto& shader = registry->emplace<Shader>(entity);
        shader.vertexShader = "../RocketEngine/Content/Shaders/Shader.vert";
        shader.fragmentShader = "../RocketEngine/Content/Shaders/Shader.frag";

        auto& material = registry->emplace<Material>(entity);
        material.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
        material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
        material.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
        material.shininess = 32.0f;
    }

    auto makeLight(entt::registry* registry) -> void
    {
        const auto lightEntity = registry->create();
        
        auto& lightComponent = registry->emplace<Light>(lightEntity);
        lightComponent.position = glm::vec3(0.0f, 10.0f, 10.0f);
        lightComponent.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
        lightComponent.specular = glm::vec3(0.5f, 0.5f, 0.5f);
        lightComponent.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    }
}

namespace RocketEngine
{
    auto Scene::instantiate(entt::registry* registry) -> void
    {
        makeCamera(registry);
        makeLight(registry);
        makeObj(registry, "../RocketEngine/Content/Models/cube.obj");
    }
}
