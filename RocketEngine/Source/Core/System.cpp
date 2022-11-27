#include <Core/System.h>
#include <Core/World.h>

namespace RocketEngine
{
    System::System(World* world)
        : world{world}
    {
    }

    auto System::begin() -> void
    {
    }

    auto System::update(double) -> void
    {
    }

    auto System::end() -> void
    {
    }

    System::~System()
    {
    }
}
