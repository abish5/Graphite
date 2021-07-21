#pragma once


#include "spdlog/sinks/stdout_color_sinks.h"
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Graphite {
	class GRAPHITE_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		static std::shared_ptr<spdlog::logger>& GetClientLogger();
	};

}

// Core log macros
#define GP_CORE_TRACE(... )		::Graphite::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GP_CORE_INFO(... )		::Graphite::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GP_CORE_WARN(... )		::Graphite::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GP_CORE_ERROR(...)		::Graphite::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GP_CORE_FATAL(... )		::Graphite::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define GP_TRACE(... )			::Graphite::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GP_INFO(... )			::Graphite::Log::GetClientLogger()->info(__VA_ARGS__)
#define GP_WARN(... )			::Graphite::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GP_ERROR(...)			::Graphite::Log::GetClientLogger()->error(__VA_ARGS__)
#define GP_FATAL(... )			::Graphite::Log::GetClientLogger()->fatal(__VA_ARGS__)
