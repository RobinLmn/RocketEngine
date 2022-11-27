#pragma once

namespace RocketEngine
{
    class World;

    class Scene
    {
    public:
        virtual auto instantiate(World* world) -> void = 0;
    };
}
