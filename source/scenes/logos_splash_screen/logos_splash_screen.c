#include "logos_splash_screen.h"
scene_t* logos_splash_screen;

Image raylib_logo_img;
Texture2D raylib_logo;

unsigned int raylib_logo_animation_frame = 0;
float raylib_logo_animation_timer = 0.f;
sprite_t* sprite;

void initialize_logos_splash_screen()
{
	raylib_logo_img = LoadImageFromMemory(".png", raylib_animated_logo_png, RAYLIB_ANIMATION_LOGO_PNG_BTYE_SIZE);
	raylib_logo = LoadTextureFromImage(raylib_logo_img);
	UnloadImage(raylib_logo_img);
	sprite = newSprite();
	addImageSheetToSprite(sprite, raylib_logo_img, (Vector2) { 0.f, 0.f }, (Vector2) { 288.f, 288.f });
}

void update_logos_splash_screen(float delta)
{
	DrawRectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, (Color) { 0xFF, 0xFF, 0xFF, 0xFF });
	raylib_logo_animation_timer += 30 * delta;
	if (raylib_logo_animation_timer >= 1) {
		if (raylib_logo_animation_frame < 75) {
			raylib_logo_animation_frame++;
		}
		raylib_logo_animation_timer = 0;
	}

	DrawTexture(sprite->textures[0], 0, 0, WHITE);
}

void destroy_logos_splash_screen()
{
	UnloadTexture(raylib_logo);
}
