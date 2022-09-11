#pragma once

#ifdef DGE_PLATFORM_WINDOWS
#if DGE_DYNAMIC_LINK
	#ifdef DGE_BUILD_DLL
		#define DGE_API __declspec(dllexport)
	#else
		#define DGE_API __declspec(dllimport)
	#endif // DGE_BUILD_DLL
#else
	#define DGE_API
#endif
#else
	#error Dilox Game Engine only supports Windows!
#endif // DGE_PLATFORM_WINDOWS

#ifdef DGE_DEBUG
	#define DGE_ENBLE_ASSERTS
#endif // DGE_DEBUG

#ifdef DGE_ENABLE_ASSERTS
	#define DGE_ASSERT(x, ...) { if(!(x)) { DGE_ERROR("Assetion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define DGE_CORE_ASSERT(x, ...) { if(!(x)) { DGE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
	#define DGE_ASSERT(x, ...)
	#define DGE_CORE_ASSERT(x, ...)
#endif // DGE_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define DGE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)