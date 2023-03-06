#include "utility.h"

float getLetterboxRatio(Vector2 resolution)
{
    #define MAX(a, b) ((a)>(b)? (a) : (b))
    #define MIN(a, b) ((a)<(b)? (a) : (b))
    return MIN((float)GetScreenWidth() / resolution.x, (float)GetScreenHeight() / resolution.y);
}

bool isInDebugMode()
{
   #if !defined(NDEBUG)
        return true;
    #endif
    return false;
}
