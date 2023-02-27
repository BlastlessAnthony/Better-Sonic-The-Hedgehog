#include "Name_Creator.h"


const char letter_table[LETTER_TABLE_SETS][LETTERS_PER_SET] = {
	{'A', 'B', 'C', 'D',   'E', 'F', 'G', 'H'},
	{'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
	{'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
	{'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f'},
	{'g', 'h', 'i',' j', 'k', 'l', 'm', 'n'},
	{'o', 'p', 'q', 'r', 's', 't', 'u', 'v'},
	{'w', 'x', 'y', 'z', ' ', '_', '-', '!'}
};


Font header_font;
Font display_font;

void name_creator()
{
	header_font = GetFontDefault();
	display_font = GetFontDefault();
	DrawTextEx(header_font, "Choose your name!", (Vector2) { (VIEW_WIDTH - MeasureTextEx(header_font, "Choose your name!", 22, 2).x)/2, 8 }, 22, 2, WHITE);
	for (int set = 0; set < LETTER_TABLE_SETS; set++) {
		for (int chr = 0; chr < LETTERS_PER_SET; chr++) {
			DrawTextCodepoint(display_font, letter_table[set][chr], (Vector2) { ((VIEW_WIDTH - (MeasureTextEx(header_font, "a", LETTER_SIZE, 0).x * LETTER_SPACING)) / 2) + (LETTER_SPACING * chr), 64 + (LINE_SPACING * set) }, LETTER_SIZE, WHITE);
		}
	}
}