#pragma once

#include <Core/System.h>

namespace RocketEngine
{
	class World;
}

namespace RocketEditor
{
	class Editor : public RocketEngine::System
	{
	public:
		Editor(RocketEngine::World*);

	public:
		virtual auto begin() -> void override;
		virtual auto update(double dt) -> void override;
		virtual auto end() -> void override;

	private:
		auto newFrame() -> void;
		auto render() -> void;
	};
}