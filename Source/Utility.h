#ifndef __BTH_UTILITY_H__
#define __BTH_UTILITY_H__
#include <raylib.h>
#include <string.h>

Vector2 FontGetGlyphSize(Font font); 
unsigned int FontGetStringWidth(Font font, char *string);
 
Vector2 AddVectors(Vector2 v1, Vector2 v2);


#endif //__BTH_UTILITY_H__