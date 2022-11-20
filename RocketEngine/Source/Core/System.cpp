#include <Core/System.h>

namespace RocketEngine
{
    System::System(entt::registry* registry)
        : registry(registry)
    {
    }

    auto System::begin() -> void
    {
    }

    auto System::update(double) -> void
    {
    }
}
