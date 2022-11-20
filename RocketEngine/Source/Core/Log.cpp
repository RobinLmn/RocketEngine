#include <Core/Log.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace RocketEngine
{
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::Initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		coreLogger = spdlog::stdout_color_mt("RocketEngine");
		coreLogger->set_level(spdlog::level::trace);
	}
}