#ifndef __BSTH_SCENE_TITLE_SCREEN_H__
#define __BSTH_SCENE_TITLE_SCREEN_H__
#include <raylib.h>
#include "scenes/scene.h"
#include "assets/assets.h"
extern void initialize_title_screen();
extern void update_title_screen(float delta);
extern void destroy_title_screen();
extern scene_t* title_screen;
#endif //__BSTH_SCENE_TITLE_SCREEN_H__
