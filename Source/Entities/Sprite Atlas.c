#include "Sprite Atlas.h"

/// @brief Instantiates a new sprite atlas.
/// @param textureAtlas The texture atlas to be copied.
/// @param textureSize The size of each frame.
/// @param framesPerRow The amount of frames vertically, remember that each frame has to be the same size. 
/// @param framesPerColumn The amount of frames horizontally, remember that each frame has to be the same size. 
/// @returns A new sprite atlas or null if the malloc failed.
SpriteAtlas* newSpriteAtlas(Texture2D textureAtlas, Vector2 textureSize, unsigned short framesPerRow, unsigned short framesPerColumn)
{
	SpriteAtlas* spriteAtlas = malloc(sizeof(SpriteAtlas));
	if (!spriteAtlas)
		return NULL;

	spriteAtlas->texture = textureAtlas;
	spriteAtlas->frame = 0;
	spriteAtlas->boundingBox = (Rectangle){0.f, 0.f, 0.f, 0.f};
	spriteAtlas->frameSize = textureSize;
	spriteAtlas->framesPerRow = framesPerRow;
	spriteAtlas->framesPerColumn = framesPerColumn;
	spriteAtlas->position = (Vector2){0.f, 0.f};
	spriteAtlas->origin = (Vector2){0.f, 0.f};
	spriteAtlas->scale = 1.f;
	spriteAtlas->rotation = 0.f;
	return spriteAtlas;
}

/// <summary>
/// Draws a port
/// </summary>
/// <param name="spriteAtlas"></param>
void drawSpriteAtlas(SpriteAtlas* spriteAtlas) {
    unsigned char maximumFrames = (spriteAtlas->framesPerColumn * spriteAtlas->framesPerRow);
    if (spriteAtlas->frame < maximumFrames) {
        spriteAtlas->animationTimer += spriteAtlas->animationSpeed;
        if (spriteAtlas->animationTimer >= 1.f) {
            spriteAtlas->frame++;
            spriteAtlas->animationTimer = 0;
        }
    }
    
	float _x, _y;
	_x = (spriteAtlas->frame % spriteAtlas->framesPerColumn) * spriteAtlas->frameSize.x;
	_y = (int)(spriteAtlas->frame / spriteAtlas->framesPerColumn) * spriteAtlas->frameSize.y;
	DrawTexturePro(spriteAtlas->texture,
		(Rectangle){_x, _y, spriteAtlas->frameSize.x, spriteAtlas->frameSize.y},
		(Rectangle){spriteAtlas->position.x, spriteAtlas->position.y, spriteAtlas->frameSize.x * spriteAtlas->scale, spriteAtlas->frameSize.y * spriteAtlas->scale},
		(Vector2){spriteAtlas->origin.x * spriteAtlas->scale, spriteAtlas->origin.y * spriteAtlas->scale},
		spriteAtlas->rotation,
		WHITE
	);
}

void destroySpriteAtlas(SpriteAtlas* spriteAtlas) { 
	free(spriteAtlas);
}
