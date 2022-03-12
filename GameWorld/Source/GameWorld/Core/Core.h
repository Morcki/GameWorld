#pragma once

#ifdef GAMEWORLD_PLATFORM_WINDOWS
	#ifdef GAMEWORLD_BUILD_DLL
		#define GAMEWORLD_API __declspec(dllexport)
	#else
		#define GAMEWORLD_API __declspec(dllimport)
	#endif
#else
	#error GameWorld only supports Windows Now!
#endif

#ifdef GAMEWORLD_ENABLE_ASSERT
	#define GAMEWORLD_ASSERT(x, ...) { if (!(x)) {GAMEWORLD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GAMEWORLD_CORE_ASSERT(x, ...) { if (!(x)) {GAMEWORLD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GAMEWORLD_ASSERT(x, ...)
	#define GAMEWORLD_CORE_ASSERT(x, ...)
#endif
