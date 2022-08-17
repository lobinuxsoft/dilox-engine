#pragma once

#ifdef DGE_PLATFORM_WINDOWS
	#ifdef DGE_BUILD_DLL
		#define DGE_API __declspec(dllexport)
	#else
		#define DGE_API __declspec(dllimport)
	#endif // DGE_BUILD_DLL
#else
	#error Dilox Game Engine only supports Windows!
#endif // DGE_PLATFORM_WINDOWS
