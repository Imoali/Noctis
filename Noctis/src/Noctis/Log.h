#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Noctis {
	class Noctis_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };
	};
}

//CORE LOG MACROS
#define NT_CORE_TRACE(...) ::Noctis::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NT_CORE_INFO(...)  ::Noctis::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NT_CORE_WARN(...)  ::Noctis::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NT_CORE_ERROR(...) ::Noctis::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NT_CORE_FATAL(...) ::Noctis::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//CLIENT LOG MACROS
#define NT_CLIENT_TRACE(...) ::Noctis::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NT_CLIENT_INFO(...)  ::Noctis::Log::GetClientLogger()->info(__VA_ARGS__)
#define NT_CLIENT_WARN(...)  ::Noctis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NT_CLIENT_ERROR(...) ::Noctis::Log::GetClientLogger()->error(__VA_ARGS__)
#define NT_CLIENT_FATAL(...) ::Noctis::Log::GetClientLogger()->fatal(__VA_ARGS__)



