#pragma once

namespace RocketEngine
{
    class World;

    class System
    {
    public:
        System(World* world);
        virtual ~System();
        
    public:
        virtual auto begin() -> void;
        virtual auto update(double dt) -> void;
        virtual auto end() -> void;
        
    protected:
        World* world;
    };
}
