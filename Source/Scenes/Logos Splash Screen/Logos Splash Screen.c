#include "Logos Splash Screen.h"
Scene* sceneLogosSplashScreen;

void initializeLogosSplashScreenScene(void)
{
    fade_opacity = 255;
    raylibLogoAnimatationTimer = 0;
    t1 = 1000;
	raylibLogoImage = LoadImageFromMemory(".png", raylib_animated_logo_png, RAYLIB_ANIMATION_LOGO_PNG_BTYE_SIZE);
	raylibLogo = newSpriteAtlas(LoadTextureFromImage(raylibLogoImage), (Vector2) { 144, 144 }, 8, 9);
    raylibLogo->origin = Vector2Divide(raylibLogo->frameSize, (Vector2){2, 2});
    raylibLogo->position = (Vector2){VIEWPORT_WIDTH/2, VIEWPORT_HEIGHT/2};
}

void updateLogosSplashScreenScene(float delta)
{
    DrawRectangle(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, (Color){0xFF, 0xFF, 0xFF, 0xFF});
    
    if (fade_opacity > 0.f) {
        DrawRectangle(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, (Color) { 0x00, 0x00, 0x00, (unsigned char)fade_opacity });
        fade_opacity -= 400 * delta;
        whichLogo = 1;
    }
    
    switch (whichLogo) {
        case 1: {
            if (raylibLogo->frame == 51 && t1 > 0) {
                raylibLogo->frame = 51;
                raylibLogo->animationSpeed = 0;
                raylibLogo->animationTimer = 0;
                t1 -= 5 * delta;
            } else {
                raylibLogo->animationSpeed = 25 * delta;
            }
            
            
            break;
        }
        default: break;
    }
    
    
    
    drawSpriteAtlas(raylibLogo);
}

void destroyLogosSplashScreenScene(void)
{
    destroySpriteAtlas(raylibLogo);
    UnloadImage(raylibLogoImage);
}
