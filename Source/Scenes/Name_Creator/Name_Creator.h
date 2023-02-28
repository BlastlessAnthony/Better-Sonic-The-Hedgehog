#ifndef __BSTH_SCENE_NAME_CREATOR_H__
#define __BSTH_SCENE_NAME_CREATOR_H__
#include <stdbool.h>
#include <stdlib.h>
#include "raylib.h"
#include "game_config.h"
#include "utility.h"
#include "entities/scene/scene.h"

#define LETTERS_PER_SET (8)
#define LETTER_TABLE_SETS (7)
#define LETTER_SPACING (20)
#define LINE_SPACING (22)
#define LETTER_SIZE (15)
#define AMOUNT_OF_LETTERS_PER_NAME (16)

extern char **letter_table;
extern Font header_font;
extern Font display_font;
extern unsigned int current_letter;
extern unsigned int current_line;
extern char name[AMOUNT_OF_LETTERS_PER_NAME];
extern unsigned int n_of_letters_in_name;

struct menu_input_ds {
	bool *left;
	bool *right;
	bool *up;
	bool *down;
	bool *select;
};

extern struct menu_input_ds *menu_input;

void initialize_name_creator();
void update_name_creator();
void destroy_name_creator();
extern scene_t *name_creator;

#endif //__BSTH_SCENE_NAME_CREATOR_H__
