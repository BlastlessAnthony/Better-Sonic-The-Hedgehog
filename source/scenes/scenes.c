#include "scenes.h"

unsigned int number_of_scenes;
scene_t** scene_tree;

void addSceneToSceneTree(scene_t* scene)
{
	scene_t** __scene_tree = realloc(scene_tree, sizeof(scene));
	if (!__scene_tree)
		return;
	
	__scene_tree[number_of_scenes] = scene;
	scene_tree = __scene_tree;
	free(__scene_tree);
}


void addNewSceneToSceneTree(void (*initialization_method)(void), void (*update_method)(void), void (*destroy_method)(void))
{
	scene_t* scene = malloc(sizeof(scene_t*));
	if (!scene) { return; }
	scene->initialize = initialization_method;
	scene->update = update_method;
	scene->destroy = destroy_method;

	addSceneToSceneTree(scene);
}