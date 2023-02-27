#include "utility.h"

Vector2 AddVectors(Vector2 v1, Vector2 v2) {
	return (Vector2) { v1.x + v2.x, v1.y + v2.y };
}

const char* GetResourcePath()
{
    #ifdef _WIN32 || _WIN64
    return TextFormat("%sresources/game/", GetApplicationDirectory());
    #elif __APPLE__ || __MACH__
    return TextFormat("%s../Resources/game/", GetApplicationDirectory());
    #elif __linux__
    return TextFormat("%s../res/game/", GetApplicationDirectory());
    #elif __unix || __unix__
    return "Unix";
    #endif
}