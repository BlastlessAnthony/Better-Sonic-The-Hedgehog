#ifndef __BSTH_SCENE_NAME_CREATOR_H__
#define __BSTH_SCENE_NAME_CREATOR_H__
#include <stdbool.h>
#include <stdlib.h>
#include "raylib.h"
#include "game_config.h"
#include "utility.h"

#define LETTERS_PER_SET (8)
#define LETTER_TABLE_SETS (7)
#define LETTER_SPACING (20)
#define LINE_SPACING (22)
#define LETTER_SIZE (15)
#define AMOUNT_OF_LETTERS_PER_NAME (16)

extern const char letter_table[LETTER_TABLE_SETS][LETTERS_PER_SET];
extern Font header_font;
extern Font display_font;
extern unsigned int current_letter;
extern unsigned int current_line;
extern char name[AMOUNT_OF_LETTERS_PER_NAME];
extern unsigned int n_of_letters_in_name;

void name_creator();

#endif //__BSTH_SCENE_NAME_CREATOR_H__