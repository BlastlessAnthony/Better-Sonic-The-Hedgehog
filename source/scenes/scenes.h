#ifndef __BSTH_SCENE_MANAGER_H__
#define __BSTH_SCENE_MANAGER_H__
#include "scene.h"
#include "name_creator/name_creator.h"


typedef struct  {
	scene_t** scenes;
	unsigned int number_of_scenes;
} scene_tree_t;

void addSceneToSceneTree(scene_t *scene);
scene_tree_t* newSceneTree();
scene_tree_t *addNewSceneToSceneTree(scene_tree_t *scene_tree, void (*initialization_method)(void), void (*update_method)(void), void (*destroy_method)(void));

#endif //__BSTH_SCENE_MANAGER_H__
