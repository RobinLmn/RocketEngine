#pragma once

#include <glm/glm.hpp>

namespace RocketEngine
{
    struct Light
    {
        glm::vec3 position;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };
}
