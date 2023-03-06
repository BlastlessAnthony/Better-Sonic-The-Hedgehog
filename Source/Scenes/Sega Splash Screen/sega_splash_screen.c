#include "sega_splash_screen.h"
scene_t* sega_splash_screen;

sprite_atlas_t *sega_logo;
Image sega_logo_img;
Sound sega_chant;
int i = 0;
float fade_opacity = 0;

unsigned int current_logo_frame = 0;
float animation_timer = 0;
void initialize_sega_splash_screen()
{
	sega_logo_img = LoadImageFromMemory(".png", sega_splash_screen_png, SEGA_SPLASH_SCREEN_PNG_BYTE_SIZE);
	sega_logo = newSpriteAtlas(LoadTextureFromImage(sega_logo_img), (Vector2){320, 224}, 1, 25);
	Wave sg_chnt_wv = LoadWaveFromMemory(".wav", sega_chant_wav, SEGA_CHANT_WAV_BYTE_SIZE);
	sega_chant = LoadSoundFromWave(sg_chnt_wv);
	UnloadWave(sg_chnt_wv);
	UnloadImage(sega_logo_img);
}

void update_sega_splash_screen(float delta)
{
	DrawRectangle(0, 0, VIEW_WIDTH, VIEW_HEIGHT, (Color) {255, 255, 255, 255});
	animation_timer += 30 * delta;
	if (animation_timer >= 1) {
		if (sega_logo->frame < 24) {
			sega_logo->frame++;
		}
		animation_timer = 0;
	}

	if (sega_logo->frame >= 24 && i == 0) {
		PlaySound(sega_chant);
		i = 1;
	}
		
	if (IsKeyPressed(KEY_ENTER) || (IsGamepadAvailable(0) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))) {
		animation_timer = 0;
		sega_logo->frame = 24;
	}

	if (i == 1 && !IsSoundPlaying(sega_chant) && fade_opacity < 255.f) {
		fade_opacity += 400 * delta;
	}

	if (fade_opacity >= 255.f)
		change_scene(logos_splash_screen);

	drawSpriteAtlas(sega_logo);
	BeginBlendMode(BLEND_MULTIPLIED);
	DrawRectangle(0, 0, (float)VIEW_WIDTH, (float)VIEW_HEIGHT, (Color) { 0x00, 0x00, 0x00, (unsigned int)fade_opacity });
	EndBlendMode();
}

void destroy_sega_splash_screen()
{
	UnloadSound(sega_chant);
}
