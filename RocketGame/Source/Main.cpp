#include <Core/Log.h>
#include <Core/Engine.h>

int main()
{
	RocketEngine::Log::Initialize();
	RocketEngine::Engine engine{};
	engine.run();
}