#ifndef __BSTH_SCENE_NAME_CREATOR_H__
#define __BSTH_SCENE_NAME_CREATOR_H__
#include "raylib.h"
#include "Config.h"
#include "Utility.h"
#define LETTERS_PER_SET (8)
#define LETTER_TABLE_SETS (7)
#define LETTER_SPACING (20)
#define LINE_SPACING (22)
#define LETTER_SIZE (15)

extern const char letter_table[LETTER_TABLE_SETS][LETTERS_PER_SET];
extern Font header_font;
extern Font display_font;

void name_creator();

#endif //__BSTH_SCENE_NAME_CREATOR_H__