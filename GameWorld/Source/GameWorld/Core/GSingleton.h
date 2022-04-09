#pragma once

#include <type_traits>

namespace GameWorld
{
	template<typename T>
	class GSingletonPublic
	{/* Do not support virtual class */
	public:
		GSingletonPublic() {}

	public:
		static T& GetInst() noexcept(std::is_nothrow_constructible<T>::value)
		{
			static T instance;
			return instance;
		}
		virtual ~GSingletonPublic() noexcept {}
		GSingletonPublic(const GSingletonPublic&) = delete;
		GSingletonPublic& operator=(const GSingletonPublic&) = delete;
	};
}