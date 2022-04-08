#pragma once

#include <type_traits>

namespace GameWorld
{
	template<typename T>
	class GSingleton
	{
	public:
		GSingleton() {}

	public:
		static T& GetInst() noexcept(std::is_nothrow_constructible<T>::value)
		{
			static T instance;
			return instance;
		}
		virtual ~GSingleton() noexcept {}
		GSingleton(const GSingleton&) = delete;
		GSingleton& operator=(const GSingleton&) = delete;
	};
}