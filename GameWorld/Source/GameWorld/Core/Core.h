#pragma once

#include <memory>

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

#define BIND_CALLBACK_FUNCTRION(func) std::bind(&func, std::placeholders::_1)
#define BIND_CLASS_CALLBACK_FUNCTRION(ClassScopedFunc) std::bind(&ClassScopedFunc, this, std::placeholders::_1)

namespace GameWorld 
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}