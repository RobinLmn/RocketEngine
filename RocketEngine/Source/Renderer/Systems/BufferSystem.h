#pragma once
#include <Core/System.h>

namespace RocketEngine
{
	class World;

	class BufferSystem final : public System
	{
	public:
		BufferSystem(World* world);

	public:
		virtual auto begin() -> void override;
		virtual auto update(double dt) -> void override;
		virtual auto end() -> void override;

	private:
	};
}
