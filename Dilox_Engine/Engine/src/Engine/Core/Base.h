#pragma once

#include <memory>

#ifdef DGE_PLATFORM_WINDOWS
	#ifdef DGE_BUILD_DLL
		#define DGE_API __declspec(dllexport)
	#else
		#define DGE_API __declspec(dllimport)
	#endif // DGE_BUILD_DLL
#else
	#error Dilox Game Engine only supports Windows!
#endif // DGE_PLATFORM_WINDOWS

#ifdef DGE_DEBUG
	#if defined(DGE_PLATFORM_WINDOWS)
		#define DGE_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn´t support debugbrak yet!"
	#endif // defined(DGE_PLATFORM_WINDOWS)
#define DGE_ENABLE_ASSERTS
#else 
	#define DGE_DEBUGBREAK()
#endif // DGE_DEBUG


#ifdef DGE_DEBUG
	#define DGE_ENBLE_ASSERTS
#endif // DGE_DEBUG

#ifdef DGE_ENABLE_ASSERTS
	#define DGE_ASSERT(x, ...) { if(!(x)) { DGE_ERROR("Assetion Failed: {0}", __VA_ARGS__); DGE_DEBUGBREAK(); } }
	#define DGE_CORE_ASSERT(x, ...) { if(!(x)) { DGE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); DGE_DEBUGBREAK();} }
#else
	#define DGE_ASSERT(x, ...)
	#define DGE_CORE_ASSERT(x, ...)
#endif // DGE_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define DGE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace DiloxGE
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