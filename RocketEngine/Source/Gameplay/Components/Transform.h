#pragma once

#include <glm/glm.hpp>

namespace RocketEngine
{
    struct Transform
    {
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
    };

    struct TransformData
    {
        glm::mat4 modelMatrix;
        glm::mat4 normalMatrix;
    };
}
