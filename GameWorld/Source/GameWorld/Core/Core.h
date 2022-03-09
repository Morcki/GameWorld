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
