#pragma once

#ifdef NT_PLATFORM_WINDOWS
	#ifdef NT_BUILD_DLL
		#define Noctis_API _declspec(dllexport)
	#else
		#define Noctis_API _declspec(dllimport)
	#endif
#endif