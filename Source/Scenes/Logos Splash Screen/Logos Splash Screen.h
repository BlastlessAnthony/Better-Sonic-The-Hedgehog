#ifndef __BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
#define __BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
#include <math.h>
#include <raylib.h>
#include "Data/Game Configuration.h"
#include "Embedded Assets/Assets.h"
#include "Entities/Sprite Atlas.h"
#include "Entities/Scene.h"
extern void initializeLogosSplashScreenScene(void);
extern void updateLogosSplashScreenScene(float delta);
extern void destroyLogosSplashScreenScene(void);
extern Scene* sceneLogosSplashScreen;

static SpriteAtlas *raylibLogo;
static Image raylibLogoImage;
static float fade_opacity;
static float raylibLogoAnimatationTimer;
static unsigned char whichLogo;
#endif //__BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
