#pragma once

#include <string>

#include "Const.h"
#include "GMacro.h"

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
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateAbstractRef(Args&& ... args)
	{// Create reference for abstract class
		Ref<T> ref;
		ref.reset(std::forward<Args>(args)...);
		return ref;
	}

	//auto add = [](int x, int y) {
	//	return x + y;
	//};
	//Proxy<decltype(add)> p{ add };
	//p(1, 2); // == 3

	template <typename Callable>
	class Proxy {
		Callable c;
	public:
		Proxy(Callable c) : c(c) {}
		template <class... Args>
		decltype(auto) operator()(Args&&... args) {
			// ...
			return std::invoke(c, std::forward<Args>(args)...);
		}
	};
}