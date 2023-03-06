#ifndef __BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
#define __BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
#include <raylib.h>
#include "scenes/scene.h"
#include "scenes/scenes.h"
#include "assets/assets.h"
#include "data/game_config.h"
#include "objects/sprite.h"
extern void initialize_logos_splash_screen();
extern void update_logos_splash_screen(float delta);
extern void destroy_logos_splash_screen();
extern scene_t* logos_splash_screen;
#endif //__BSTH_SCENE_LOGOS_SPLASH_SCREEN_H__
