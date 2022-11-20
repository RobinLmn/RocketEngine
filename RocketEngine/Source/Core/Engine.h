#pragma once

#include <Core/Window.h>
#include <Gameplay/World.h>
#include <Renderer/Renderer.h>

namespace RocketEngine
{
	class Engine final
	{
	public:
		Engine();

		auto run() -> void;

	private:
		Window window;
		World world;
		Renderer renderer;
	};
}