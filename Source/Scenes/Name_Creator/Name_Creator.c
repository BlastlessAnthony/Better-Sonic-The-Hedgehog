#include "Name_Creator.h"


const unsigned int size_o_allowed_chars = 0x33;
const char allowed_characters[0x33] = {
	'A', 'B', 'C', 'D', 'E', 'F',
	'G', 'H', 'I', 'J', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S',
	'T', 'U', 'V', 'W', 'X', 'Y',
	'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i',
	'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x',
	'y', 'z'
};

const unsigned int character_offset = 0x0C;
const unsigned int line_offset = 0x0F;
int n_of_lines = 0x00;
unsigned int characters_on_line = 0;
Color charactor_color[0x33];

Vector2 char_offset = { 0, 0 };

const unsigned int chars_per_line = 0x05;
Vector2 char_position;
void name_creator()
{
	const Font font = GetFontDefault();
	
	char_position = (Vector2){ 32, 32 };
	char_offset = (Vector2){ 0, 0 };
	

	for (unsigned int _i = 0; _i < 0x19; _i += 0x01) {
		charactor_color[_i] = WHITE;
	}

	for (unsigned int n_of_chars = 0; n_of_chars < size_o_allowed_chars; n_of_chars += 0x01)
	{
		if (characters_on_line == chars_per_line) {
			char_offset.y += line_offset;
			characters_on_line = 0;
			n_of_lines += 0x01;
		}

		characters_on_line += 0x01;
		char_offset.x += character_offset;
		DrawTextCodepoint(font, allowed_characters[n_of_chars], AddVectors(char_position, char_offset), 15, charactor_color[n_of_chars]);
		
	}
}
