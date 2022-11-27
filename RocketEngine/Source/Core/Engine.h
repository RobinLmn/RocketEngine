#pragma once

#include <Core/Window.h>
#include <Core/World.h>
#include <Renderer/Renderer.h>

struct GLFWwindow;

namespace RocketEngine
{

	class Engine final
	{
	public:
		Engine(Engine&&) = delete;
		Engine(const Engine&) = delete;
		Engine operator=(const Engine&) = delete;

	public:
		[[nodiscard]] static auto get() -> Engine&;
		auto run() -> void;

		auto isKeyPressed(int key) const -> bool;
		auto getAspectRatio() const -> float;
		auto getNativeWindow() -> GLFWwindow*;
		auto pushRenderCallback(std::function<void()> callback) -> void;
		
		template<typename T_Scene>
		auto pushScene() -> void
		{
			world.pushScene<T_Scene>();
		}

	private:
		Engine();

	private:
		Window window;
		World world;
		Renderer renderer;
	};
}