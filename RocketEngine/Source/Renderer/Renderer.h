#pragma once

#include <Core/System.h>
#include <vector>
#include <functional>

namespace RocketEngine
{
	class World;

	class Renderer final
	{
	public:
		Renderer(World* world);
		~Renderer();

	public:
		auto begin() -> void;
		auto draw(double dt) -> void;
		auto end() -> void;
		auto pushRenderCallback(std::function<void()> callback) -> void;

	private:
		template<typename T_System>
		auto addSystem() -> void;

	private:
		World* world;
		std::vector<System*> systems;
		std::vector<std::function<void()>> renderCallbacks;
	};
}