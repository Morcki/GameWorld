#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "GameWorld/Core/Core.h"

namespace GameWorld
{
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return sptrCoreLogger; };
		inline static Ref<spdlog::logger>& GetClientLogger() { return sptrClientLogger; };
	
	private:
		static Ref<spdlog::logger> sptrCoreLogger;
		static Ref<spdlog::logger> sptrClientLogger;

	};
}
#define GAMEWORLD_CORE_TRACE(...) ::GameWorld::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define GAMEWORLD_CORE_INFO(...)  ::GameWorld::Log::GetCoreLogger()->info(__VA_ARGS__);
#define GAMEWORLD_CORE_WARN(...)  ::GameWorld::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define GAMEWORLD_CORE_ERROR(...) ::GameWorld::Log::GetCoreLogger()->error(__VA_ARGS__);
#define GAMEWORLD_CORE_FATAL(...) ::GameWorld::Log::GetCoreLogger()->fatal(__VA_ARGS__);


#define GAMEWORLD_TRACE(...) ::GameWorld::Log::GetClientLogger()->trace(__VA_ARGS__);
#define GAMEWORLD_INFO(...)  ::GameWorld::Log::GetClientLogger()->info(__VA_ARGS__);
#define GAMEWORLD_WARN(...)  ::GameWorld::Log::GetClientLogger()->warn(__VA_ARGS__);
#define GAMEWORLD_ERROR(...) ::GameWorld::Log::GetClientLogger()->error(__VA_ARGS__);
#define GAMEWORLD_FATAL(...) ::GameWorld::Log::GetClientLogger()->fatal(__VA_ARGS__);

