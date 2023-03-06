#include "sprite.h"

sprite_t* newSprite()
{
	sprite_t* sprite = malloc(sizeof(sprite));
	if (!sprite)
		return NULL;

	//sprite->textures = NULL;
	sprite->frame = 0;
	sprite->amount_of_frames = 0;
	sprite->bounding_box = (Rectangle){ 0.f, 0.f, 0.f, 0.f };
	sprite->position = (Vector2){ 0.f, 0.f };
	sprite->origin = (Vector2){ 0.f, 0.f };
	return sprite;
}

void setSpriteHitbox(sprite_t* sprite, Rectangle bounding_box){sprite->bounding_box = bounding_box;}
void addFrametoSprite(sprite_t* sprite, Texture2D texture) {
	sprite->textures[sprite->amount_of_frames] = texture;
	sprite->amount_of_frames++;
}

void addImageSheetToSprite(sprite_t *sprite, Image image_strip, Vector2 scan_start_position, Vector2 frame_size)
{
	for (int y = 0; y < (image_strip.height/frame_size.y); y++ ) {
		for (int x = 0; x < (image_strip.width / frame_size.x); x++) {
			addFrametoSprite(sprite,
				LoadTextureFromImage(ImageFromImage(image_strip,
					(Rectangle) {
				scan_start_position.x + (frame_size.x * x), scan_start_position.y + (frame_size.y * y), frame_size.x, frame_size.y
			})));
		}
	}
}