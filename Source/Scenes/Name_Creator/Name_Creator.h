#ifndef __BSTH_SCENE_NAME_CREATOR_H__
#define __BSTH_SCENE_NAME_CREATOR_H__
#include "raylib.h"
#include "Config.h"
#include "Utility.h"

extern const Font font;
extern const unsigned int size_o_allowed_chars;
extern const char allowed_characters[0x33];

extern Color charactor_color[0x33];
extern unsigned int characters_on_line;
extern const unsigned int character_offset;
extern const unsigned int line_offset;
extern const unsigned int chars_per_line;
extern int n_of_lines;

extern Vector2 char_position;

extern Vector2 char_offset;

void name_creator();

#endif //__BSTH_SCENE_NAME_CREATOR_H__