#ifndef __BSTH_GAME_CONFIG_H__
#define __BSTH_GAME_CONFIG_H__

#include <stdbool.h>

struct user_config_t {
	bool graphics_show_cursor;
	bool graphics_fullscreen;
	unsigned int graphics_monitor;
	bool stat_show_fps;
};

extern struct user_config_t user_config;

void load_user_config();
#endif //__BSTH_GAME_CONFIG_H__