#ifndef __BSTH_SCENE_MANAGER_H__
#define __BSTH_SCENE_MANAGER_H__
#include "scene.h"
#include "scenes/sega_splash_screen/sega_splash_screen.h"
#include "scenes/logos_splash_screen/logos_splash_screen.h"
#include "scenes/title_screen/title_screen.h"

extern void instaniate_scenes();
extern scene_t* current_scene;
extern void change_scene(scene_t *scene);
#endif //__BSTH_SCENE_MANAGER_H__
