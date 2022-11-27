#include "Scene.h"

#include <Core/World.h>

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
    auto makeCamera(RocketEngine::World* world) -> void
    {
        const auto cameraEntity = world->spawnEntity();

        auto& cameraTransform = world->getOrAddComponents<RocketEngine::Transform>(cameraEntity);
        cameraTransform.position = { 0.f, 0.f, -15.f };
        cameraTransform.scale = { 1.f, 1.f, 1.f };
        cameraTransform.rotation = { 0.f, 0.f, 0.f };

        auto& cameraComponent = world->getOrAddComponents<RocketEngine::Camera>(cameraEntity);
        cameraComponent.isMainCamera = true;
        cameraComponent.near = 0.03f;
        cameraComponent.far = 100.f;
        cameraComponent.aspect = 1920.f / 1080.f;
        cameraComponent.fov = glm::radians(45.f);
        cameraComponent.speed = 0.5f;
        cameraComponent.sensitivity = 1.f;
    }

    auto makeObj(RocketEngine::World* world, const char* obj) -> void
    {
        const auto entity = world->spawnEntity();

        auto& entityMesh = world->getOrAddComponents<RocketEngine::Model>(entity);
        entityMesh.path = obj;

        auto& entityTransform = world->getOrAddComponents<RocketEngine::Transform>(entity);
        entityTransform.position = { 0.f, 0.f, 0.f };
        entityTransform.scale = { 0.1f, 0.1f, 0.1f };
        entityTransform.rotation = { 45.f, 45.f, 45.f };

        auto& shader = world->getOrAddComponents<RocketEngine::Shader>(entity);
        shader.vertexShader = "../RocketEngine/Content/Shaders/Shader.vert";
        shader.fragmentShader = "../RocketEngine/Content/Shaders/Shader.frag";

        auto& material = world->getOrAddComponents<RocketEngine::Material>(entity);
        material.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
        material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
        material.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
        material.shininess = 32.0f;
    }

    auto makeLight(RocketEngine::World* world) -> void
    {
        const auto lightEntity = world->spawnEntity();

        auto& lightComponent = world->getOrAddComponents<RocketEngine::Light>(lightEntity);
        lightComponent.position = glm::vec3(0.0f, 10.0f, 10.0f);
        lightComponent.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
        lightComponent.specular = glm::vec3(0.5f, 0.5f, 0.5f);
        lightComponent.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    }
}

namespace RocketGame
{
    auto Scene::instantiate(RocketEngine::World* world) -> void
    {
        makeCamera(world);
        makeLight(world);
        makeObj(world, "../RocketEngine/Content/Models/cube.obj");
    }
}