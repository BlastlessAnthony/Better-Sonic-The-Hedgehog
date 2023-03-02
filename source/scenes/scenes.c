#include "scenes.h"

unsigned int number_of_scenes = 0;
scene_t** scene_tree;


scene_tree_t* newSceneTree() {
	scene_tree_t *__scene_tree = malloc(sizeof(scene_tree_t*));
	if (!__scene_tree)
		return NULL;

	__scene_tree->scenes = NULL;
	__scene_tree->number_of_scenes = 0;

	return __scene_tree;
}

void addSceneToSceneTree(scene_t* scene)
{

}

/*
scene_t **addNewSceneToSceneTree(void(*initialization_method)(void), void(*update_method)(void), void(*destroy_method)(void))
{
	scene_t* _scene = malloc(sizeof(scene_t*));
	if (!_scene)
		return NULL;

	_scene->initialize = initialization_method;
	_scene->update = update_method;
	_scene->destroy = destroy_method;

	scene_t** __scene_tree = malloc(sizeof(scene_tree) + sizeof(_scene));
	if (!__scene_tree)
		return NULL;

	__scene_tree[number_of_scenes] = malloc(sizeof(_scene));
	__scene_tree[number_of_scenes] = _scene;
	return __scene_tree;
}
*/

scene_tree_t* addNewSceneToSceneTree(scene_tree_t* scene_tree, void (*initialization_method)(void), void (*update_method)(void), void (*destroy_method)(void))
{
	scene_t* _scene = malloc(sizeof(scene_t*));
	if (!_scene)
		return NULL;

	_scene->initialize = initialization_method;
	_scene->update = update_method;
	_scene->destroy = destroy_method;

	scene_tree_t *__scene_tree = malloc(sizeof(scene_tree));
	if (!__scene_tree)
		return NULL;

	__scene_tree->scenes = malloc(sizeof(scene_tree->scenes) + sizeof(_scene));
	__scene_tree->scenes = scene_tree->scenes;
	__scene_tree->number_of_scenes = scene_tree->number_of_scenes;
	__scene_tree->scenes[__scene_tree->number_of_scenes] = malloc(sizeof(_scene));
	__scene_tree->scenes[__scene_tree->number_of_scenes] = _scene;
	__scene_tree->number_of_scenes++;
	return __scene_tree;
}