#pragma once
#include "Core.h"
#include <spdlog/spdlog.h>

namespace GameWorld
{
	class GAMEWORLD_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sptrCoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return sptrClientLogger; };
	
	private:
		static std::shared_ptr<spdlog::logger> sptrCoreLogger;
		static std::shared_ptr<spdlog::logger> sptrClientLogger;

	};
}
#define GAMEWORLD_CORE_TRACE(...) ::GameWorld::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define GAMEWORLD_CORE_INFO(...)  ::GameWorld::Log::GetCoreLogger()->info(__VA_ARGS__);
#define GAMEWORLD_CORE_WARN(...)  ::GameWorld::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define GAMEWORLD_CORE_ERROR(...) ::GameWorld::Log::GetCoreLogger()->error(__VA_ARGS__);
#define GAMEWORLD_CORE_FATAL(...) ::GameWorld::Log::GetCoreLogger()->fatal(__VA_ARGS__);

#define GAMEWORLD_CLIENT_TRACE(...) ::GameWorld::Log::GetClientLogger()->trace(__VA_ARGS__);
#define GAMEWORLD_CLIENT_INFO(...)  ::GameWorld::Log::GetClientLogger()->info(__VA_ARGS__);
#define GAMEWORLD_CLIENT_WARN(...)  ::GameWorld::Log::GetClientLogger()->warn(__VA_ARGS__);
#define GAMEWORLD_CLIENT_ERROR(...) ::GameWorld::Log::GetClientLogger()->error(__VA_ARGS__);
#define GAMEWORLD_CLIENT_FATAL(...) ::GameWorld::Log::GetClientLogger()->fatal(__VA_ARGS__);

