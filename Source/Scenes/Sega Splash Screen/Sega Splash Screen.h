#ifndef __BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
#define __BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
#include <raylib.h>
#include "Data/Game Configuration.h"
#include "Entities/Scene.h"
#include "Entities/Sprite Atlas.h"
#include "Embedded Assets/Assets.h"
#include "Scenes/Scene Manager.h"

extern void initializeSegaSplashScreenScene();
extern void updateSegaSplashScreenScene(float delta);
extern void destroySegaSplashScreen();
extern Scene * sceneSegaSplashScreen;
#endif //__BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
