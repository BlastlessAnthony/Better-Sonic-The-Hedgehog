#include "scenes.h"
scene_t* current_scene = NULL;

/// <summary>
/// Instantiates all the scenes before the game starts.
/// </summary>
void instaniate_scenes() {
	sega_splash_screen = newScene(initialize_sega_splash_screen, update_sega_splash_screen, destroy_sega_splash_screen);
	logos_splash_screen = newScene(initialize_logos_splash_screen, update_logos_splash_screen, destroy_logos_splash_screen);
	title_screen = newScene(initialize_title_screen, update_title_screen, destroy_title_screen);
}

/// <summary>
/// Changes the current scene.
/// </summary>
/// <param name="scene">The scene to change to.</param>
void change_scene(scene_t* scene) {
	if (current_scene)
		(current_scene->destroy)();
	current_scene = NULL;

	current_scene = malloc(sizeof(scene_t*));
	current_scene = scene;
	if (scene) {
		(current_scene->initialize)();
	}
		
}
