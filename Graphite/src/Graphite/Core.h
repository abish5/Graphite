#pragma once

#ifdef GP_PLATFORM_WINDOWS
	#ifdef GP_BUILD_DLL
		#define GRAPHITE_API __declspec(dllexport)
	#else 
		#define GRAPHITE_API __declspec(dllimport)
	#endif
#else
	#error Graphite only supports Windows!!!
#endif

#define BIT(x) (1 << x)