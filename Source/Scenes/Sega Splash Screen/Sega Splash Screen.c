#include "Sega Splash Screen.h"
Scene* sceneSegaSplashScreen;

void initializeSegaSplashScreenScene(void)
{
    i = 0;
    fade_opacity = 0;
    animation_timer = 0;
    
	segaLogoImage = LoadImageFromMemory(".png", sega_splash_screen_png, SEGA_SPLASH_SCREEN_PNG_BYTE_SIZE);
	segaLogo = newSpriteAtlas(LoadTextureFromImage(segaLogoImage), (Vector2) { 320, 224 }, 5, 5);
	
	segaChantWave = LoadWaveFromMemory(".wav", sega_chant_wav, SEGA_CHANT_WAV_BYTE_SIZE);
	segaChant = LoadSoundFromWave(segaChantWave);
}

void updateSegaSplashScreenScene(float delta)
{
	DrawRectangle(0, 0, (int)VIEWPORT_WIDTH, (int)VIEWPORT_HEIGHT, (Color) {255, 255, 255, 255});
    
	segaLogo->animationSpeed = 25 * delta;

	if (segaLogo->frame >= 24 && i == 0) {
		PlaySound(segaChant);
		i = 1;
	}
		
	if (IsKeyPressed(KEY_ENTER) || (IsGamepadAvailable(0) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))) {
		segaLogo->frame = 24;
	}

	if (i == 1 && !IsSoundPlaying(segaChant) && fade_opacity < 255.f) {
		fade_opacity += 400 * delta;
	}

	if (fade_opacity >= 255.f)
		changeToScene(sceneLogosSplashScreen);

	drawSpriteAtlas(segaLogo);
    
    if (fade_opacity < 255) {
        BeginBlendMode(BLEND_MULTIPLIED);
            DrawRectangle(0, 0, (float)VIEWPORT_WIDTH, (float)VIEWPORT_HEIGHT, (Color) { 0x00, 0x00, 0x00, (unsigned int)fade_opacity });
        EndBlendMode();
    }
}

void destroySegaSplashScreen(void)
{
	destroySpriteAtlas(segaLogo);
	UnloadSound(segaChant);
    UnloadImage(segaLogoImage);
    UnloadWave(segaChantWave);
}
