#include "name_creator.h"


char **letter_table;


Font header_font;
Font display_font;

unsigned int current_letter = 0;
unsigned int current_line = 0;
unsigned int n_of_letters_in_name = 0;

char name[AMOUNT_OF_LETTERS_PER_NAME];

struct menu_input_ds *menu_input;

scene_t* name_creator;

void initialize_name_creator()
{
	letter_table = malloc( sizeof(char*) * (LETTERS_PER_SET*LETTER_TABLE_SETS) );

	struct menu_input_ds *menu_input = malloc(sizeof(struct menu_input_ds*));
}

void update_name_creator()
{
	menu_input->up = IsKeyPressed(KEY_UP);
	menu_input->down = IsKeyPressed(KEY_DOWN);
	menu_input->left = IsKeyPressed(KEY_LEFT);
	menu_input->right = IsKeyPressed(KEY_RIGHT);
	menu_input->select = IsKeyPressed(KEY_ENTER);

	if (menu_input->left && current_letter > 0) {current_letter--;}
	if (menu_input->right && current_letter < (LETTERS_PER_SET - 1)) {current_letter++; }
	if (menu_input->down && current_line < (LETTER_TABLE_SETS - 1)) {current_line++;} 
	if (menu_input->up && current_line > 0) {current_line--;}
	/*
	DrawTextEx(header_font, "Choose your name!", (Vector2) { (VIEW_WIDTH - MeasureTextEx(header_font, "Choose your name!", 22, 2).x)/2, 8 }, 22, 2, WHITE);
	DrawTextEx(display_font, name, (Vector2) { (VIEW_WIDTH - MeasureTextEx(header_font, name, LETTER_SIZE, 2).x)/2, 32+8 }, LETTER_SIZE, 2, WHITE);
	for (unsigned int set = 0; set < LETTER_TABLE_SETS; set++) {
		for (unsigned int chr = 0; chr < LETTERS_PER_SET; chr++) {
			DrawTextCodepoint(display_font, letter_table[set][chr], 
				(Vector2) { ((VIEW_WIDTH - (MeasureTextEx(header_font, "a", LETTER_SIZE, 0).x * LETTER_SPACING)) / 2) + (LETTER_SPACING * chr), 64 + (LINE_SPACING * set) }, LETTER_SIZE, WHITE);
			if (current_line == set && current_letter == chr) {
				DrawCircleLines(((VIEW_WIDTH - (MeasureTextEx(header_font, "a", LETTER_SIZE, 0).x * LETTER_SPACING)) /2) + (LETTER_SPACING * current_letter) + (MeasureTextEx(display_font, "a", LETTER_SIZE, 0).x/2), 64 + (LINE_SPACING * current_line) + (MeasureTextEx(display_font, "a", LETTER_SIZE, 0).y)/2, LETTER_SIZE/2, BLUE);
			}
			
		}
	}

	if (menu_input->select)
	{
		if (letter_table[current_line][current_letter] != '<' && n_of_letters_in_name < AMOUNT_OF_LETTERS_PER_NAME) {
			name[n_of_letters_in_name] = letter_table[current_line][current_letter];
			n_of_letters_in_name++;
		}
		else if (n_of_letters_in_name > 0 && letter_table[current_line][current_letter] == '<') {
			name[n_of_letters_in_name - 1] = '\0';
			n_of_letters_in_name--;
		}
	}
	*/
}

void destroy_name_creator()
{

}
