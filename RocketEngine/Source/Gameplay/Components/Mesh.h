#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace RocketEngine
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
    };

    struct StaticMesh
    {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;
    };

    struct MeshPath
    {
        std::string path;
    };
}
