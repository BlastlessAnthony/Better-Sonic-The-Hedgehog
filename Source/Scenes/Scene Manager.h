#ifndef __BSTH_SCENE_MANAGER_H__
#define __BSTH_SCENE_MANAGER_H__
#include "Entities/Scene.h"
#include "Sega Splash Screen/Sega Splash Screen.h"
#include "Logos Splash Screen/Logos Splash Screen.h"

extern void instaniateScenes();
extern Scene* currentScene;
extern void changeToScene(Scene * Scene);
#endif //__BSTH_SCENE_MANAGER_H__
