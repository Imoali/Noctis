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

#define BIT(x) (1 << x)