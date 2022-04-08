#include "PrecompiledHeader.h"

#include "GLogSystem.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace GameWorld
{

	GLogSystem::GLogSystem()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		core_logger_ = spdlog::stdout_color_mt("GameWorld");
		core_logger_->set_level(spdlog::level::trace);

		client_logger_ = spdlog::stdout_color_mt("Application");
		client_logger_->set_level(spdlog::level::trace);
	}

}