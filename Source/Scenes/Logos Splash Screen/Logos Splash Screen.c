#include "Logos Splash Screen.h"
Scene* sceneLogosSplashScreen;

void initializeLogosSplashScreenScene(void)
{
    fade_opacity = 255;
    raylibLogoAnimatationTimer = 0;
	raylibLogoImage = LoadImageFromMemory(".png", raylib_animated_logo_png, RAYLIB_ANIMATION_LOGO_PNG_BTYE_SIZE);
	raylibLogo = newSpriteAtlas(LoadTextureFromImage(raylibLogoImage), (Vector2) { 144, 144 }, 8, 9);
	
}

void updateLogosSplashScreenScene(float delta)
{
    DrawRectangle(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, (Color){0xFF, 0xFF, 0xFF, 0xFF});
    
    if (fade_opacity > 0.f) {
            DrawRectangle(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, (Color) { 0x00, 0x00, 0x00, (unsigned char)fade_opacity });
        fade_opacity -= 400 * delta;
    }
    
    
    raylibLogo->animationSpeed = 25 * delta;
    
    drawSpriteAtlas(raylibLogo);
    
    DrawText(TextFormat("%f/%i", raylibLogoAnimatationTimer, raylibLogo->frame), 0, 96, 15, BLUE);
}

void destroyLogosSplashScreenScene(void)
{
    destroySpriteAtlas(raylibLogo);
    UnloadImage(raylibLogoImage);
}
