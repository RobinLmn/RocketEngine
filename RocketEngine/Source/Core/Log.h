#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <cassert>

namespace RocketEngine
{
	class Log
	{
	public:
		static void Initialize();

		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

#ifdef ROCKET_DEBUG
#define ROCKET_ERROR(...)    ::RocketEngine::Log::coreLogger->error(__VA_ARGS__)
#define ROCKET_WARN(...)     ::RocketEngine::Log::coreLogger->warn(__VA_ARGS__)
#define ROCKET_INFO(...)     ::RocketEngine::Log::coreLogger->info(__VA_ARGS__)
#define ROCKET_TRACE(...)    ::RocketEngine::Log::coreLogger->trace(__VA_ARGS__)
#define ROCKET_ASSERT(expr, ...)	if(!(expr)){ ROCKET_ERROR(__VA_ARGS__); }
#else 
#define ROCKET_FATAL(...)
#define ROCKET_ERROR(...)
#define ROCKET_WARN(...)
#define ROCKET_INFO(...)
#define ROCKET_TRACE(...)
#define ROCKET_ASSERT(expr, ...)
#endif