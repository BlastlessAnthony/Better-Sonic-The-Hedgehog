#ifndef __BTH_UTILITY_H__
#define __BTH_UTILITY_H__
#include <raylib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
const char* GetResourcePath();
bool isInDebugMode();
float getLetterboxRatio(Vector2 resolution);
#endif //__BTH_UTILITY_H__
