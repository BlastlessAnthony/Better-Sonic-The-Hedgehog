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

EmbeddedFont* newEmbeddedFont(const char *font_type, const unsigned char font_data, const uint32_t font_data_size, const uint32_t default_font_size)
{
    EmbeddedFont *_font = malloc(sizeof(EmbeddedFont*));
    if (!_font) 
        return NULL;
    
    if (strcasecmp(font_type, ".otf") || strcasecmp(font_type, ".ttf"))
        _font->type;
        
    _font->data = font_data;
    _font->byte_size = font_data_size;
    _font->default_size = default_font_size;
    _font->characters = malloc(sizeof(unsigned char*)  * 256);
    for (int i = 0; i < 95; i++) _font->characters[i] = 32 + i;   // Basic ASCII characters
    for (int i = 0; i < 255; i++) _font->characters[96 + i] = 0x400 + i;   // Cyrillic character
    _font->font = LoadFontFromMemory(_font->type, _font->data, _font->byte_size, _font->default_size, _font->characters, 512);

    return _font;
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
