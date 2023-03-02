#include "utility.h"
#include <ctype.h>

char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}
float getLetterboxRatio(Vector2 resolution)
{
    #define MAX(a, b) ((a)>(b)? (a) : (b))
    #define MIN(a, b) ((a)<(b)? (a) : (b))
    return MIN((float)GetScreenWidth() / resolution.x, (float)GetScreenHeight() / resolution.y);
}

const char* GetResourcePath()
{
    #ifdef _WIN32 || _WIN64
        return TextFormat("%sresources/game/", GetApplicationDirectory());
    #elif __APPLE__ || __MACH__

        #if !defined(NDEBUG)
            return TextFormat("%sresources/", GetApplicationDirectory());
        #endif
            return TextFormat("%s../Resources/", GetApplicationDirectory());
    
    #elif __linux__
        return TextFormat("%s../res/", GetApplicationDirectory());
    #endif
}

bool isInDebugMode()
{
   #if !defined(NDEBUG)
        return true;
    #endif
    return false;
}
