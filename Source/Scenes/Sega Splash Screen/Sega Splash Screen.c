#include "Sega Splash Screen.h"
Scene* sceneSegaSplashScreen;

SpriteAtlas *segaLogo;

Sound segaChant;
int i = 0;
float fade_opacity = 0;
float animation_timer = 0;

void initializeSegaSplashScreenScene()
{
	Image segaLogoImage = LoadImageFromMemory(".png", sega_splash_screen_png, SEGA_SPLASH_SCREEN_PNG_BYTE_SIZE);
	segaLogo = newSpriteAtlas(LoadTextureFromImage(segaLogoImage), (Vector2) { 320, 224 }, 5, 5);
	UnloadImage(segaLogoImage);

	Wave segaChantWave = LoadWaveFromMemory(".wav", sega_chant_wav, SEGA_CHANT_WAV_BYTE_SIZE);
	segaChant = LoadSoundFromWave(segaChantWave);
	UnloadWave(segaChantWave);
}

void updateSegaSplashScreenScene(float delta)
{
	DrawRectangle(0, 0, (int)VIEWPORT_WIDTH, (int)VIEWPORT_HEIGHT, (Color) {255, 255, 255, 255});
	animation_timer += 30 * delta;
	if (animation_timer >= 1) {
		if (segaLogo->frame < 24) {
			segaLogo->frame++;
		}
		animation_timer = 0;
	}

	if (segaLogo->frame >= 24 && i == 0) {
		PlaySound(segaChant);
		i = 1;
	}
		
	if (IsKeyPressed(KEY_ENTER) || (IsGamepadAvailable(0) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))) {
		animation_timer = 0;
		segaLogo->frame = 24;
	}

	if (i == 1 && !IsSoundPlaying(segaChant) && fade_opacity < 255.f) {
		fade_opacity += 400 * delta;
	}

	if (fade_opacity >= 255.f)
		changeToScene(sceneLogosSplashScreen);

	drawSpriteAtlas(segaLogo);
	BeginBlendMode(BLEND_MULTIPLIED);
	DrawRectangle(0, 0, (float)VIEWPORT_WIDTH, (float)VIEWPORT_HEIGHT, (Color) { 0x00, 0x00, 0x00, (unsigned int)fade_opacity });
	EndBlendMode();
}

void destroySegaSplashScreen()
{
	//destroySpriteAtlas(segaLogo);
	UnloadSound(segaChant);
}
