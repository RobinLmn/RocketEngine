#pragma once
#include <Core/System.h>
#include <Gameplay/Components/Mesh.h>

namespace RocketEngine
{
    class MeshLoadingSystem final : public System
    {
    public:
        MeshLoadingSystem(World* world);
    
    public:
        virtual auto begin() -> void override;
        virtual auto update(double dt) -> void override;
        
    private:
        auto loadMesh(Mesh& mesh, const char* path) -> void;
    };
}
