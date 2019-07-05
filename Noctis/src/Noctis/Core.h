#pragma once

#ifdef NT_PLATFORM_WINDOWS
	#if HZ_DYNAMIC_LINK
		#ifdef NT_BUILD_DLL
			#define NOCTIS_API _declspec(dllexport)
		#else
			#define NOCTIS_API _declspec(dllimport)
		#endif
	#else
		#define NOCTIS_API
	#endif
#else
	#error Noctis only supports windows
#endif

#ifdef NT_DEBUG
#define NT_ENABLE_ASSERTS
#endif 


#ifdef NT_ENABLE_ASSERTS
	#define NT_CORE_ASSERT(x, ...) {if(!x) {NT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define NT_CLIENT_ASSERT(x, ...) {if(!x) {NT_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define NT_CORE_ASSERT(x, ...)
	#define NT_CLIENT_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define NT_BIND_FN(x) std::bind(&x, this, std::placeholders::_1)