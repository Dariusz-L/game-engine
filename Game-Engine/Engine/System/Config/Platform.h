#pragma once

#ifdef _MSC_VER
	#define _PLATFORM_WINDOWS_
#elif staticlibrary
	#define _PLATFORM_EDITOR_
#else 
	#define _PLATFORM_ANDROID_
#endif