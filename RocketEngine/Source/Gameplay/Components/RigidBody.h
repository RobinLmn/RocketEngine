#pragma once

#include <glm/glm.hpp>

namespace RocketEngine
{
    struct RigidBody
    {
        float mass;
        glm::vec3 velocity;
        glm::vec3 force;
    };
}
