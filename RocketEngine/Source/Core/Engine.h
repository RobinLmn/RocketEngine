#pragma once

#include <Core/Window.h>
#include <Core/World.h>
#include <Renderer/Renderer.h>

namespace RocketEngine
{
	class Engine final
	{
	public:
		Engine();

	public:
		auto run() -> void;

	private:
		Window window;
		World world;
		Renderer renderer;
	};
}