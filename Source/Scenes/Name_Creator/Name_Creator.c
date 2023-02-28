#include "name_creator.h"


const char letter_table[LETTER_TABLE_SETS][LETTERS_PER_SET] = {
	{'A', 'B', 'C', 'D',   'E', 'F', 'G', 'H'},
	{'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
	{'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
	{'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f'},
	{'g', 'h', 'i',' j', 'k', 'l', 'm', 'n'},
	{'o', 'p', 'q', 'r', 's', 't', 'u', 'v'},
	{'w', 'x', 'y', 'z', ' ', '_', '-', '<'}
};


Font header_font;
Font display_font;

unsigned int current_letter = 0;
unsigned int current_line = 0;
unsigned int n_of_letters_in_name = 0;

char name[AMOUNT_OF_LETTERS_PER_NAME];

bool init = false;
void name_creator()
{
	
	if (!init) {
		header_font = GetFontDefault();
		display_font = LoadFont(TextFormat("%sfonts/PixelOperator/PixelOperator-Bold.ttf", GetResourcePath()));
		init = true;
	}
		

	bool input_left = IsKeyPressed(KEY_LEFT);
	bool input_right = IsKeyPressed(KEY_RIGHT);
	bool input_up = IsKeyPressed(KEY_UP);
	bool input_down = IsKeyPressed(KEY_DOWN);
	bool input_select = IsKeyPressed(KEY_ENTER);

	if (input_left && current_letter > 0) {current_letter--;}
	if (input_right && current_letter < (LETTERS_PER_SET - 1)) {current_letter++; }
	if (input_down && current_line < (LETTER_TABLE_SETS - 1)) {current_line++;} 
	if (input_up && current_line > 0) {current_line--;}
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

	if (input_select)
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
	
}