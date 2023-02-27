#include "Utility.h"

Vector2 FontGetGlyphSize(Font font)
{
	return (Vector2) { font.recs->width, font.recs->height };
}

unsigned int FontGetStringWidth(Font font, char* string)
{
	return (FontGetGlyphSize(font).x * strlen(string));
}

Vector2 AddVectors(Vector2 v1, Vector2 v2) {
	return (Vector2) { v1.x + v2.x, v1.y + v2.y };
}