#include <Core/Engine.h>
#include <Core/Log.h>

namespace RocketEngine
{
    Engine::Engine()
        : world{}
        , window{ 800, 800, "RocketEngine" }
        , renderer{}
    {
    }

    auto Engine::run() -> void
    {
        ROCKET_INFO("Running RocketEngine");

        std::chrono::high_resolution_clock clock{};
        using seconds = std::chrono::duration<double, std::ratio<1>>;
        auto lastTime = clock.now();

        world.begin();

        while (window.isOpen())
        {
            const double dt = std::chrono::duration_cast<seconds>(clock.now() - lastTime).count();
            lastTime = clock.now();

            window.processInput();
            world.update(dt);
            renderer.draw();
        }
    }
}