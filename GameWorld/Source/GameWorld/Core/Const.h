#pragma once

#include "glm/glm.hpp"

#ifdef GAMEWORLD_PLATFORM_WINDOWS
	typedef char GW_CHAR;

	typedef char GW_INT8;
	typedef unsigned char GW_UINT8;

	//typedef int16_t GW_INT16;
	//typedef unsigned int16_t GW_UINT16;

	typedef int GW_INT32;
	typedef unsigned int GW_UINT32;

	typedef float GW_FLOAT32;
	typedef double GW_FLOAT64;

	typedef bool GW_BOOL;
#endif

	constexpr GW_FLOAT32 M_PI = 3.14159265358979323846f;