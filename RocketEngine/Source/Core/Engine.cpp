#include <Core/Engine.h>
#include <Core/Log.h>

namespace RocketEngine
{
    Engine::Engine()
        : window{ 1920, 1080, "RocketEngine" }
        , world{} 
        , renderer{ &world }
    {
    }

    auto Engine::run() -> void
    {
        ROCKET_INFO("Running RocketEngine");

        std::chrono::high_resolution_clock clock{};
        using seconds = std::chrono::duration<double, std::ratio<1>>;
        auto lastTime = clock.now();

        world.begin();
        renderer.begin();

        while (window.isOpen())
        {
            const double dt = std::chrono::duration_cast<seconds>(clock.now() - lastTime).count();
            lastTime = clock.now();

            window.processInput();
            world.update(dt);
            renderer.draw(dt);
        }

        renderer.end();
        world.end();
    }

    auto Engine::get() -> Engine&
    {
        static Engine engine{};
        return engine;
    }

    auto Engine::isKeyPressed(int key) const -> bool
    {
        return window.isKeyPressed(key);
    }

    auto Engine::getAspectRatio() const -> float
    {
        return window.getAspectRatio();
    }

    auto Engine::getNativeWindow() -> GLFWwindow*
    {
        return window.getNativeWindow();
    }

    auto Engine::pushRenderCallback(std::function<void()> callback) -> void
    {
        renderer.pushRenderCallback(callback);
    }
}