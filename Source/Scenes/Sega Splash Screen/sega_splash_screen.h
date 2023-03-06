#ifndef __BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
#define __BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
#include <raylib.h>
#include "scenes/scene.h"
#include "scenes/scenes.h"
#include "assets/assets.h"
#include "objects/sprite.h"
#include "data/game_config.h"
extern void initialize_sega_splash_screen();
extern void update_sega_splash_screen(float delta);
extern void destroy_sega_splash_screen();
extern scene_t *sega_splash_screen;
#endif //__BSTH_SCENE_SEGA_SPLASH_SCREEN_H__
