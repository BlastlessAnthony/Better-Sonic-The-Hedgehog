#ifndef __BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
#define __BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
#include <raylib.h>
#include "Data/Game Configuration.h"
#include "Entities/Scene.h"
#include "Entities/Sprite Atlas.h"
#include "Embedded Assets/Assets.h"
#include "Scenes/Scene Manager.h"

extern void initializeSegaSplashScreenScene(void);
extern void updateSegaSplashScreenScene(float delta);
extern void destroySegaSplashScreen(void);
extern Scene * sceneSegaSplashScreen;

static SpriteAtlas *segaLogo;
static Image segaLogoImage;
static Sound segaChant;
static Wave segaChantWave;
static int i;
static float fade_opacity;
static float animation_timer;
#endif //__BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
