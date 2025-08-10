#include "Core.h"

#ifdef PLATFORM_WINDOWS
	Platform g_Platform = WINDOWS;
#else
	Platform g_Platform = LINUX;
#endif
