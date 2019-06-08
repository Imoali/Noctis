#pragma once

#ifdef NT_PLATFORM_WINDOWS
	#ifdef NT_BUILD_DLL
		#define NOCTIS_API _declspec(dllexport)
	#else
		#define NOCTIS_API _declspec(dllimport)
	#endif
#else
	#error Noctis only supports windows
#endif

#ifdef NT_ENABLE_ASSERTS
	#define NT_CORE_ASSERT(x, ...) {if(!x) {NT_CORE_ERROR("Assertion Failed: {0}", _VA_ARGS_); _debugbreak();}}
	#define NT_CLIENT_ASSERT(x, ...) {if(!x) {NT_CLIENT_ERROR("Assertion Failed: {0}", _VA_ARGS_); _debugbreak();}}
#else
	#define NT_CORE_ASSERT(x, ...)
	#define NT_CLIENT_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)