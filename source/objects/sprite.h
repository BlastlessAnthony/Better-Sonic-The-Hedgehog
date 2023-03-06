#ifndef __RAYLIB_UTILITY_SPRITE_H__
#define __RAYLIB_UTILITY_SPRITE_H__
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <raylib.h>
#include <raymath.h>
typedef struct {
	Texture2D texture;
	unsigned int frame;
	unsigned int frames_per_column;
	unsigned int frames_per_row;
	Vector2 frame_size;
	Vector2 position;
	Vector2 origin;
	Rectangle bounding_box;
	float scale;
	float rotation;
} sprite_atlas_t;

sprite_atlas_t* newSpriteAtlas(Texture2D texture_atlas, Vector2 texture_size, unsigned int frames_per_row, unsigned int frames_per_column);
void drawSpriteAtlas(sprite_atlas_t *sprite);
void destroySpriteAtlas(sprite_atlas_t *sprite);
#endif //__RAYLIB_UTILITY_SPRITE_H__
