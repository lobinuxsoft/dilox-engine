/*
*Basado en https://www.youtube.com/watch?v=dZr-53LAlOw&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=7
*/

#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace DiloxGE
{
	class DGE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define DGE_CORE_TRACE(...)		::DiloxGE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DGE_CORE_INFO(...)		::DiloxGE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DGE_CORE_WARN(...)		::DiloxGE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DGE_CORE_ERROR(...)		::DiloxGE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DGE_CORE_FATAL(...)		::DiloxGE::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define DGE_TRACE(...)			::DiloxGE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DGE_INFO(...)			::DiloxGE::Log::GetClientLogger()->info(__VA_ARGS__)
#define DGE_WARN(...)			::DiloxGE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DGE_ERROR(...)			::DiloxGE::Log::GetClientLogger()->error(__VA_ARGS__)
#define DGE_FATAL(...)			::DiloxGE::Log::GetClientLogger()->fatal(__VA_ARGS__)