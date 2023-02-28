#include "utility.h"

Vector2 AddVectors(Vector2 v1, Vector2 v2) {
	return (Vector2) { v1.x + v2.x, v1.y + v2.y };
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
