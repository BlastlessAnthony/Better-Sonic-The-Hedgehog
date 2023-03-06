#include "logos_splash_screen.h"
scene_t* logos_splash_screen;

Image raylib_logo_img;
sprite_atlas_t *raylib_logo;

unsigned int raylib_logo_animation_frame = 0;
float raylib_logo_animation_timer = 0.f;

void initialize_logos_splash_screen()
{
	raylib_logo_img = LoadImageFromMemory(".png", raylib_animated_logo_png, RAYLIB_ANIMATION_LOGO_PNG_BTYE_SIZE);
	raylib_logo = newSpriteAtlas(LoadTextureFromImage(raylib_logo_img), (Vector2){144, 144}, 8, 9);
	UnloadImage(raylib_logo_img);
	raylib_logo->scale = 1.f;
}

void update_logos_splash_screen(float delta)
{
	DrawRectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, (Color) { 0xFF, 0xFF, 0xFF, 0xFF });
	raylib_logo_animation_timer += 15 * delta;
	if (raylib_logo_animation_timer >= 1) {
		if (raylib_logo->frame < 75) {
			raylib_logo->frame++;
		}
		raylib_logo_animation_timer = 0;
	}
	drawSpriteAtlas(raylib_logo);
}

void destroy_logos_splash_screen()
{
	//destroySpriteAtlas(raylib_logo);
}
