#include "Utility.h"

float getLetterboxRatio(Vector2 resolution)
{
    #define MAX(a, b) ((a)>(b)? (a) : (b))
    #define MIN(a, b) ((a)<(b)? (a) : (b))
    return MIN((float)GetScreenWidth() / resolution.x, (float)GetScreenHeight() / resolution.y);
}

unsigned char isInDebugMode(void)
{
   #if !defined(NDEBUG)
        return true;
    #endif
    return false;
}

unsigned char isOperatingSystem(const char *OS)
{
    return strcasecmp(OS_PLATFORM, OS) == 0 ? 1 : 0;
}
