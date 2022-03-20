#include "PrecompiledHeader.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace GameWorld
{
	std::shared_ptr<spdlog::logger> Log::s_ptr_core_logger_;
	std::shared_ptr<spdlog::logger> Log::s_ptr_client_logger_;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		s_ptr_core_logger_ = spdlog::stdout_color_mt("GameWorld");
		s_ptr_core_logger_->set_level(spdlog::level::trace);

		s_ptr_client_logger_ = spdlog::stdout_color_mt("Application");
		s_ptr_client_logger_->set_level(spdlog::level::trace);
	}

}