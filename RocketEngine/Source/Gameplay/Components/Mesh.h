#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace RocketEngine
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };

    struct StaticMesh
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };

    struct Model
    {
        std::string path;
    };
}
