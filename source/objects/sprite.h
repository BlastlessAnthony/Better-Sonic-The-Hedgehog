#ifndef __RAYLIB_UTILITY_SPRITE_H__
#define __RAYLIB_UTILITY_SPRITE_H__
#include <stdlib.h>
#include <raylib.h>
typedef struct {
	Texture2D textures[1024];
	unsigned int amount_of_frames;
	unsigned int frame;
	Vector2 position;
	Vector2 origin;
	Rectangle bounding_box;
} sprite_t;

sprite_t* newSprite();

void setSpriteHitbox(sprite_t *sprite, Rectangle bounding_box);
void addFrametoSprite(sprite_t* sprite, Texture2D texture);
void addImageSheetToSprite(sprite_t* sprite, Image image_strip, Vector2 scan_start_position, Vector2 frame_size);
#endif //__RAYLIB_UTILITY_SPRITE_H__
