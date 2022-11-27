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
		
		template<typename T_Scene>
		auto inline addScene() -> void
		{
			world.addScene<T_Scene>();
		}

	private:
		Window window;
		World world;
		Renderer renderer;
	};
}