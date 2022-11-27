#pragma once

#include <Core/System.h>
#include <vector>

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

	private:
		template<typename T_System>
		auto addSystem() -> void;

	private:
		World* world;
		std::vector<System*> systems;
	};
}