#include "sprite.h"

/// @brief Instaniates a new sprite atlas via a texture.
/// @param texture_atlas ...
/// @param texture_size The size of each frame.
/// @param frames_per_row The amount of frames vertically, remember that each frame has to be the same size. 
/// @param frames_per_column The amount of frames horizontally, remember that each frame has to be the same size. 
/// @returns A new sprite atlas or null if the malloc failed.
sprite_atlas_t* newSpriteAtlas(Texture2D texture_atlas, Vector2 texture_size, unsigned int frames_per_row, unsigned int frames_per_column)
{
	sprite_atlas_t* sprite = malloc(sizeof(sprite_atlas_t*));
	if (!sprite)
		return NULL;

	sprite->texture = texture_atlas;
	sprite->frame = 0;
	sprite->bounding_box = (Rectangle){0.f, 0.f, 0.f, 0.f};
	sprite->frame_size = texture_size;
	sprite->frames_per_row = frames_per_row;
	sprite->frames_per_column = frames_per_column;
	sprite->position = (Vector2){0.f, 0.f};
	sprite->origin = (Vector2){0.f, 0.f};
	sprite->scale = 1.f;
	sprite->rotation = 0.f;
	return sprite;
}


void drawSpriteAtlas(sprite_atlas_t *sprite){
	float _x, _y;
	_x = (sprite->frame % sprite->frames_per_column) * sprite->frame_size.x;
	_y = (int)(sprite->frame / sprite->frames_per_column) * sprite->frame_size.y;
	DrawTexturePro(sprite->texture,
		(Rectangle){_x, _y, sprite->frame_size.x, sprite->frame_size.y},
		(Rectangle){sprite->position.x, sprite->position.y, sprite->frame_size.x * sprite->scale, sprite->frame_size.y * sprite->scale},
		(Vector2){sprite->origin.x * sprite->scale, sprite->origin.y * sprite->scale},
		sprite->rotation,
		WHITE
	);
}

/*

void drawSprite(Sprite* sprite, float x, float y, float ang, float scale, Color c) 
{
    float ox, oy;
    ox = (sprite->frame % sprite->framesWide) * sprite->frameSize.x;
    oy = (int)(sprite->frame / sprite->framesWide) * sprite->frameSize.y;
    DrawTexturePro(sprite->texture, (Rectangle){ox, oy, sprite->frameSize.x,sprite->frameSize.y}, 
                                    (Rectangle){x, y, sprite->frameSize.x * scale, sprite->frameSize.y * scale}, 
                                    (Vector2){sprite->origin.x * scale, sprite->origin.y * scale}, ang, c);

}
*/