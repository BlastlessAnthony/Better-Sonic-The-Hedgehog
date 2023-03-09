#ifndef __BTH_UTILITY_H__
#define __BTH_UTILITY_H__
#include <string.h>
#include <raylib.h>
#include "Platform.h"
extern unsigned char isInDebugMode(void);
extern float getLetterboxRatio(Vector2 resolution);
extern unsigned char isOperatingSystem(const char *OS);
#endif //__BTH_UTILITY_H__
