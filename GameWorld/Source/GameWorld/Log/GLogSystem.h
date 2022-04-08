#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "GameWorld/Core/Core.h"
#include "GameWorld/Core/GSingleton.h"

namespace GameWorld
{
	class GLogSystem final : public GSingleton<GLogSystem>
	{
	public:
		GLogSystem();

		inline const Ref<spdlog::logger>& GetCoreLogger() { return core_logger_; };
		inline const Ref<spdlog::logger>& GetClientLogger() { return client_logger_; };
	
	private:
		Ref<spdlog::logger> core_logger_;
		Ref<spdlog::logger> client_logger_;

	};
}
#define GAMEWORLD_CORE_TRACE(...) ::GameWorld::GLogSystem::GetInst().GetCoreLogger()->trace(__VA_ARGS__);
#define GAMEWORLD_CORE_INFO(...)  ::GameWorld::GLogSystem::GetInst().GetCoreLogger()->info(__VA_ARGS__);
#define GAMEWORLD_CORE_WARN(...)  ::GameWorld::GLogSystem::GetInst().GetCoreLogger()->warn(__VA_ARGS__);
#define GAMEWORLD_CORE_ERROR(...) ::GameWorld::GLogSystem::GetInst().GetCoreLogger()->error(__VA_ARGS__);
#define GAMEWORLD_CORE_FATAL(...) ::GameWorld::GLogSystem::GetInst().GetCoreLogger()->critical(__VA_ARGS__);


#define GAMEWORLD_TRACE(...) ::GameWorld::GLogSystem::GetInst().GetClientLogger()->trace(__VA_ARGS__);
#define GAMEWORLD_INFO(...)  ::GameWorld::GLogSystem::GetInst().GetClientLogger()->info(__VA_ARGS__);
#define GAMEWORLD_WARN(...)  ::GameWorld::GLogSystem::GetInst().GetClientLogger()->warn(__VA_ARGS__);
#define GAMEWORLD_ERROR(...) ::GameWorld::GLogSystem::GetInst().GetClientLogger()->error(__VA_ARGS__);
#define GAMEWORLD_FATAL(...) ::GameWorld::GLogSystem::GetInst().GetClientLogger()->critical(__VA_ARGS__);

