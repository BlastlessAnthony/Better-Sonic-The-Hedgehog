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
    whichLogo = 1;
}

void updateLogosSplashScreenScene(float delta)
{
    fade_opacity = Clamp(fade_opacity, 0, 255);
    switch (whichLogo) {
        case 1: {
            DrawRectangle(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, (Color){0xFF, 0xFF, 0xFF, 0xFF});
            if (raylibLogo->frame == 51 && t1 > 0) {
                raylibLogo->frame = 51;
                raylibLogo->animationSpeed = 0;
                raylibLogo->animationTimer = 0;
                t1 -= 5 * delta;
            } else {
                raylibLogo->animationSpeed = 25 * delta;
            }
            DrawTextEx(GetFontDefault(), TextFormat("Made with Raylib %s", RAYLIB_VERSION), (Vector2){VIEWPORT_WIDTH/2 - (MeasureTextEx(GetFontDefault(), TextFormat("Made with Raylib %s", RAYLIB_VERSION), 18, 2).x)/2, 0}, 18, 2, BLACK);
            drawSpriteAtlas(raylibLogo);
            
            if (raylibLogo->frame < 71) {
                fade_opacity -= 100 * delta;
            }
            
            if (raylibLogo->frame >= 71) {
                fade_opacity += 100 * delta;
                if (fade_opacity >= 255) {
                    whichLogo = 2;
                }
            }
            break;
        }
            
        case 2: {
            DrawRectangle(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, (Color){0x00, 0x00, 0x00, 0xFF});
        }
        default: break;
    }
    
    BeginBlendMode(BLEND_MULTIPLIED);
        DrawRectangle(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, (Color) { 0x00, 0x00, 0x00, (unsigned char)fade_opacity });
    EndBlendMode();
    
    DrawText(TextFormat("%f", fade_opacity), 0, 0, 15, WHITE);
    
}

void destroyLogosSplashScreenScene(void)
{
    destroySpriteAtlas(raylibLogo);
    UnloadImage(raylibLogoImage);
}
