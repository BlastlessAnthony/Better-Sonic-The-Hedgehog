#ifndef __BTH_UTILITY_H__
#define __BTH_UTILITY_H__
#include <raylib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
const char* GetResourcePath();
bool isInDebugMode();
float getLetterboxRatio(Vector2 resolution);
typedef struct {
    char *type;
    unsigned char *data;
    unsigned int *byte_size;
    unsigned int default_size;
    unsigned char *characters;
    unsigned int *glyphs;
    Font font;
} EmbeddedFont;

EmbeddedFont *newEmbeddedFont(const char *font_type, const unsigned char font_data, const uint32_t font_data_size, const uint32_t default_font_size );
#endif //__BTH_UTILITY_H__
