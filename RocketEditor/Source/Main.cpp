#include <Core/Log.h>
#include <Core/Engine.h>

#include "Scene.h"

int main()
{
	RocketEngine::Log::Initialize();

	auto& engine = RocketEngine::Engine::get();
	engine.pushScene<RocketEditor::Scene>();
	engine.run();
}