#ifndef __RAYLIB_UTILITY_SPRITE_ATLAS_H__
#define __RAYLIB_UTILITY_SPRITE_ATLAS_H__
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

typedef struct {
	Texture2D texture;
	unsigned short frame;
	unsigned short framesPerColumn;
	unsigned short framesPerRow;
	Vector2 frameSize;
	Vector2 position;
	Vector2 origin;
	float scale;
	float rotation;
	Rectangle boundingBox;
} SpriteAtlas;

extern SpriteAtlas* newSpriteAtlas(Texture2D textureAtlas, Vector2 textureSize, unsigned short framesPerRow, unsigned short framesPerColumn);
extern void drawSpriteAtlas(SpriteAtlas *spriteAtlas);
extern void destroySpriteAtlas(SpriteAtlas *spriteAtlas);

#endif //__RAYLIB_UTILITY_SPRITE_ATLAS_H__
