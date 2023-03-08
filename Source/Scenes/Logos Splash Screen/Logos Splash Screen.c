#include "Logos Splash Screen.h"
Scene* sceneLogosSplashScreen;


SpriteAtlas *raylibLogo;
float raylib_logo_animation_timer = 0.f;

void initializeLogosSplashScreenScene()
{
	Image raylibLogoImage = LoadImageFromMemory(".png", raylib_animated_logo_png, RAYLIB_ANIMATION_LOGO_PNG_BTYE_SIZE);
	raylibLogo = newSpriteAtlas(LoadTextureFromImage(raylibLogoImage), (Vector2) { 144, 144 }, 8, 9);
	UnloadImage(raylibLogoImage);
}

void updateLogosSplashScreenScene(float delta)
{
	DrawRectangle(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, (Color) { 0xFF, 0xFF, 0xFF, 0xFF });

	raylib_logo_animation_timer += 15 * delta;
	if (raylib_logo_animation_timer >= 1) {
		if (raylibLogo->frame < 75) {
			raylibLogo->frame++;
		}
		raylib_logo_animation_timer = 0;
	}
	drawSpriteAtlas(raylibLogo);
}

void destroyLogosSplashScreenScene()
{
	//destroySpriteAtlas(raylib_logo);
}
