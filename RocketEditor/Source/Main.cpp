#include <Core/Log.h>
#include <Core/Engine.h>

#include "Scene.h"

int main()
{
	RocketEngine::Log::Initialize();
	RocketEngine::Engine engine{};

	engine.addScene<RocketGame::Scene>();
	engine.run();
}