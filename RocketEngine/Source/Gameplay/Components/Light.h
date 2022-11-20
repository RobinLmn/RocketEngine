#pragma once

#include <glm/glm.hpp>

namespace RocketEngine
{
    struct Light
    {
        float ambientStrength;
        float diffuseStrength;
        glm::vec3 color;
    };
}
