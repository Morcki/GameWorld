#include "PrecompiledHeader.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace GameWorld
{
	std::shared_ptr<spdlog::logger> Log::sptrCoreLogger;
	std::shared_ptr<spdlog::logger> Log::sptrClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		sptrCoreLogger = spdlog::stdout_color_mt("GameWorld");
		sptrCoreLogger->set_level(spdlog::level::trace);

		sptrClientLogger = spdlog::stdout_color_mt("Application");
		sptrClientLogger->set_level(spdlog::level::trace);
	}

}