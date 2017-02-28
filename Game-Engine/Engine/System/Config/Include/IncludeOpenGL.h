#pragma once

#include "..\Platform.h"

#if defined(_PLATFORM_WINDOWS_) || defined(_PLATFORM_EDITOR_)	
	#include <GL\glew.h>
#else
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#endif