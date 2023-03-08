#ifndef __BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
#define __BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
#include <raylib.h>
#include "Data/Game Configuration.h"
#include "Embedded Assets/Assets.h"
#include "Entities/Sprite Atlas.h"
#include "Entities/Scene.h"
extern void initializeLogosSplashScreenScene();
extern void updateLogosSplashScreenScene(float delta);
extern void destroyLogosSplashScreenScene();
extern Scene* sceneLogosSplashScreen;
#endif //__BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
